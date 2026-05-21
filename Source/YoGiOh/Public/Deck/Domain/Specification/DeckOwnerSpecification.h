#pragma once

class DeckOwnerSpecification
{
public:
	static bool isSatisfiedByOwner(const FString& Owner, FString& OutError);
};
