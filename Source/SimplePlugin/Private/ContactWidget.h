#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STableViewBase.h"
#include "Widgets/Views/STableRow.h"
#include "ContactInfo.h"

class  SQueryInfoWidget : public SMultiColumnTableRow< TSharedPtr< FQueryInfo > >
{
public:
	
	SLATE_BEGIN_ARGS( SQueryInfoWidget )
		
		{}
		SLATE_ARGUMENT(TSharedPtr< FQueryInfo>, Item)

	SLATE_END_ARGS()
	
	/**
	 * Generates a widget for task graph events list column
	 *
	 * @param InArgs   A declaration from which to construct the widget
	 */
	virtual TSharedRef< SWidget > GenerateWidgetForColumn( const FName& ColumnName ) override;


	/**
	 * Construct the widget
	 *
	 * @param InArgs   A declaration from which to construct the widget
	 */
	void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView );

private:

	TSharedPtr< FQueryInfo> Item;

};

class SContactWidget: public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SContactWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TSharedRef<ITableRow> MakeContactInfoWidget(TSharedPtr<struct FContactInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);

	void CreateContactInfoList();

	TArray<TSharedPtr<struct FContactInfo>> ContactInfoList;

	//---------------
	void OnGetChildrenForQueryGroup( TSharedPtr<FQueryInfo> InItem, TArray<TSharedPtr<FQueryInfo> >& OutChildren );

	TSharedRef<ITableRow> MakeQueryInfoWidget(TSharedPtr<struct FQueryInfo> InItem, const TSharedRef<STableViewBase>& OwnerTable);

	void CreateQueryInfoList();
	TArray<TSharedPtr<struct FQueryInfo>> QueryInfoList;


	static const FName GroupColumnName;
	static const FName NameColumnName;
	static const FName AddressColumnName;
};