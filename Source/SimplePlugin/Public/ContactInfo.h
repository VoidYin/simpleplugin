#pragma once

;struct FContactInfo
{
	FString ContactName;
	FString ContactAddress;

	FContactInfo(const FString& InContactName, const FString& InContactAddress)
		: ContactName(InContactName)
		, ContactAddress(InContactAddress)
	{}
};

struct FQueryInfo
{
	bool bIsGroup;

	// if group
	FString GroupName;
	TArray< TSharedPtr< FQueryInfo > > Children;


	// if a leaf
	FString ContactName;
	FString ContactAddress;

	FQueryInfo(bool IsGroup, const FString& InGroupName, const FString& InContactName, const FString& InContactAddress)
		: ContactName(InContactName)
		, ContactAddress(InContactAddress)
		, bIsGroup(IsGroup)
		, GroupName(InGroupName)
	{}
};