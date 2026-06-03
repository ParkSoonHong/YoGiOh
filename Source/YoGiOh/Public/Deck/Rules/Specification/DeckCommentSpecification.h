#pragma once

class DeckCommentSpecification
{
public:
	static bool IsSatisfiedByComment(const FString& Name, FString& OutError);
};
