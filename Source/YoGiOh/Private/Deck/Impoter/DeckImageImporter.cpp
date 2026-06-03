// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/Impoter/DeckImageImporter.h"

// 윈도우 파일 탐색기를 열기 위한 모듈
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
// png, jpg 같은 이미지 파일을 읽기 위한 모듈
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
// 파일 읽기용
#include "Misc/FileHelper.h"
// 경로(Saved 폴더 등) 관리용
#include "Misc/Paths.h"
// 파일 복사, 폴더 생성용
#include "HAL/FileManager.h"
// 언리얼 텍스쳐 클래스
#include "Engine/Texture2D.h"

/*
	전체 흐름
	1. 파일 탐색기 열기
	2. 사용자가 이미지 선택
	3. 선택한 이미지를 Saved/CopyImages 에 복사
	4. 복사된 이미지를 Texture2D 로 변환
	5. UI 에 썸네일로 표시 가능
*/
bool UDeckImageImporter::ImportDeckImage(FString& OutSavedPath, UTexture2D*& OutTexture)
{
	// 사용자가 선택한 원본 이미지 경로
	FString selectedPath;
	// 파일 탐색기 열기 실패 시 종료
	if (!OpenImageDialog(selectedPath))
	{
		return false;
	}
	// 게임 내부 Saved 폴더로 이미지 복사
	if (!CopyImageToSavedFolder(selectedPath,OutSavedPath))
	{
		return false;
	}
	// 복사된 이미지를 Texture2D 로 변환
	
	FString Path = FPaths::ProjectSavedDir() / TEXT("CopyImages") / OutSavedPath;
	OutTexture = LoadTextureFromFile(Path);
	// 텍스쳐 생성 성공 여부 반환
	return OutTexture != nullptr;
}
/*
	윈도우 파일 탐색기 열기
*/
bool UDeckImageImporter::OpenImageDialog(FString& OutSelectedPath)
{
	// 윈도우 파일 탐색기를 사용할 수 있는 객체 가져오기
	IDesktopPlatform* desktopPlatform = FDesktopPlatformModule::Get();
	// 실패 시 종료
	if (!desktopPlatform)
	{
		return false;
	}

	// 선택된 파일 목록 저장 배열
	TArray<FString> outFiles;
	
	/*
		파일 탐색기 열기
		사용자가 png 또는 jpg 파일 선택 가능
	*/
	bool bOpened =
		desktopPlatform->OpenFileDialog(
			nullptr, // 부모 윈도우
			TEXT("Select Deck Image"), // 탐색기 제목
			TEXT(""),// 기본 폴더
			TEXT(""),// 기본 파일명
			TEXT("Image Files (*.png;*.jpg)|*.png;*.jpg"),
			EFileDialogFlags::None,
			outFiles
		);
	// 사용자가 취소했거나 파일 선택 안 했으면 실패
	if (!bOpened || outFiles.Num() == 0)
	{
		return false;
	}
	// 첫 번째 선택 파일 저장
	OutSelectedPath = outFiles[0];

	return true;
}
/*
	선택한 이미지를 게임 내부 Saved 폴더로 복사
*/
bool UDeckImageImporter::CopyImageToSavedFolder(const FString& SourcePath, FString& OutSavedPath)
{
	/*
		언리얼 프로젝트의 Saved 폴더 경로
		예시:
		MyProject/Saved/
	*/
	FString saveDir = FPaths::ProjectSavedDir() / TEXT("CopyImages");
	/*
			폴더 생성
			true:
			중간 폴더까지 자동 생성
	*/
	if (!IFileManager::Get().MakeDirectory(*saveDir, true))
	{
		UE_LOG(LogTemp,Error,TEXT("Could not create Image directory %s"),*saveDir);
		return false;
	}
	/*
		파일 확장자 추출
		예:
		test.png -> png
	*/
	FString extension = FPaths::GetExtension(SourcePath);
	/*
		중복 방지를 위해 랜덤 파일 이름 생성 - FGuid::NewGuid() sms 128비트 랜덤값이라 경우의 수가 매우 작다.
		예:
		1A2B3C4D.png
	*/
	FString fileName = FGuid::NewGuid().ToString() + TEXT(".") + extension;
	/*
		최종 저장 경로
		예:
		Saved/CopyImages/1A2B3C4D.png
	*/
	FString DestPath = saveDir / fileName;
	OutSavedPath = fileName;
	/*
		파일 복사
		왼쪽:
		복사될 위치
		오른쪽:
		원본 파일
	*/
	return IFileManager::Get().Copy(*DestPath,*SourcePath) == COPY_OK;
}
/*
	이미지 파일을 Texture2D 로 변환
*/
UTexture2D* UDeckImageImporter::LoadTextureFromFile(const FString& FilePath)
{
	if (FilePath.IsEmpty())
	{
		return nullptr;
	}
	/*
		이미지 파일의 바이너리 데이터 저장 배열
		png/jpg 파일 내용이 들어감
	*/
	TArray<uint8> fileData;
	/*
		파일 읽기 실패 시 종료
	*/
	if (!FFileHelper::LoadFileToArray(fileData,*FilePath))
	{
		return nullptr;
	}
	/*
		이미지 처리 모듈 가져오기
		png/jpg 해석 가능
	*/
	IImageWrapperModule& imageWrapperModule =
		FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	/*
		파일 형식 자동 판별
		png인지 jpg인지 확인
	*/
	EImageFormat Format =  imageWrapperModule.DetectImageFormat(
			fileData.GetData(),
			fileData.Num());
	
	//이미지 해석 객체 생성
	TSharedPtr<IImageWrapper> imageWrapper =
		imageWrapperModule.CreateImageWrapper(Format);
	// 실패 시 종료
	if (!imageWrapper.IsValid())
	{
		return nullptr;
	}
	/*
		압축된 png/jpg 데이터를 읽기 준비
		아직은 압축 상태
	*/
	if (!imageWrapper->SetCompressed(fileData.GetData(),fileData.Num()))
	{
		return nullptr;
	}
	/*
		압축 해제된 실제 픽셀 데이터 저장 배열
		RGBA 픽셀값들이 들어감
	*/
	TArray<uint8> rawData;
	/*
		압축 해제
		BGRA:
		픽셀 색상 형식
		8:
		8비트 컬러
	*/
	if (!imageWrapper->GetRaw(ERGBFormat::BGRA,8,rawData))
	{
		return nullptr;
	}
	/*
		언리얼 텍스쳐 생성
		이미지 크기와 동일한 Texture2D 생성
	*/
	UTexture2D* texture =
		UTexture2D::CreateTransient(imageWrapper->GetWidth(),imageWrapper->GetHeight());

	if (!texture)
	{
		return nullptr;
	}
	/*
		텍스쳐 메모리 잠금
		이제 픽셀 데이터를 직접 복사 가능
	*/
	void* textureData = texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	//rawData 픽셀을 텍스쳐 메모리에 복사
	FMemory::Memcpy(textureData,rawData.GetData(),rawData.Num());
	//메모리 잠금 해제
	texture->GetPlatformData()->Mips[0].BulkData.Unlock();
	/*
		GPU 에 텍스쳐 업데이트 요청
		이걸 해야 화면에 보임
	*/
	texture->UpdateResource();

	// 완성된 Texture2D 반환
	return texture;
}

UTexture2D* UDeckImageImporter::LoadDeckImage(const FString& FileName)
{
	FString path = FPaths::ProjectSavedDir() / TEXT("CopyImages")/ FileName;

	return LoadTextureFromFile(path);
}
