#pragma once

class UserNameSpecification
{
public:
	static bool IsSatisfiedByName(const FString& Name, FString& OutError);
};
