#include "ContactWidget.h"
#include "STextBlock.h"
#include "SListView.h"
#include "SBoxPanel.h"
#include "STreeView.h"
#include "SComboBox.h"
#define LOCTEXT_NAMESPACE "ContactWidget"

const FName SContactWidget::GroupColumnName(TEXT("ID"));
const FName SContactWidget::NameColumnName(TEXT("Frame"));
const FName SContactWidget::AddressColumnName(TEXT("Type"));

TSharedRef<SWidget> SContactWidget::MakeNameInfoWidget(TSharedPtr<FString> InItem)
{
	return SNew(STextBlock)
		.Text(FText::FromString(*InItem));
}

void SContactWidget::CreateNameInfoList()
{
	NameInfoList.Add(MakeShareable(new FString("AAA")));
	NameInfoList.Add(MakeShareable(new FString("bbb")));
	NameInfoList.Add(MakeShareable(new FString("ccc")));
	NameInfoList.Add(MakeShareable(new FString("dddd")));
}

FText SContactWidget::GetSelectedNameInfo() const
{
	if (NameInfoComboBox->GetSelectedItem().IsValid())
	{
		return FText::FromString(*NameInfoComboBox->GetSelectedItem());
	}
	else
	{
		return LOCTEXT("AutomationRequestedFilterComboLabel", "All Tests");
	}
}

void SContactWidget::Construct(const FArguments& InArgs)
{
	CreateContactInfoList();
	CreateQueryInfoList();
	CreateNameInfoList();

	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		[

				SNew(SListView<TSharedPtr<FContactInfo>>)
				.ListItemsSource(&ContactInfoList)
				.OnGenerateRow(this, &SContactWidget::MakeContactInfoWidget)
		]
		+ SHorizontalBox::Slot()
		[

				SNew(STreeView<TSharedPtr<FQueryInfo>>)
				.TreeItemsSource(&QueryInfoList)
				.OnGenerateRow(this, &SContactWidget::MakeQueryInfoWidget)
				.OnGetChildren(this, &SContactWidget::OnGetChildrenForQueryGroup)
				//.HeaderRow(
				//		SNew(SHeaderRow)
				//		// ID
				//		+SHeaderRow::Column(GroupColumnName)
				//		.HAlignCell(HAlign_Left)
				//		[
				//			SNew(STextBlock)
				//			.Text(LOCTEXT("QueryInfoID", "ID"))
				//		]
				//		+SHeaderRow::Column(NameColumnName)
				//		.HAlignCell(HAlign_Left)
				//		[
				//			SNew(STextBlock)
				//			.Text(LOCTEXT("QueryInfoName", "Name"))
				//		]
				//		+SHeaderRow::Column(AddressColumnName)
				//		.HAlignCell(HAlign_Left)
				//		[
				//			SNew(STextBlock)
				//			.Text(LOCTEXT("QueryInfoAddress", "Address"))
				//		]
				//)
		]
		+ SHorizontalBox::Slot()
		[
			SAssignNew(NameInfoComboBox, SComboBox<TSharedPtr<FString>>)
			.ContentPadding(FMargin(6.0f, 2.0f))
			.OptionsSource(&NameInfoList)
			.OnGenerateWidget(this, &SContactWidget::MakeNameInfoWidget)
			[
				SNew(STextBlock)
				.Text(this, &SContactWidget::GetSelectedNameInfo)
			]
		]
			
	];
}

TSharedRef<ITableRow> SContactWidget::MakeContactInfoWidget(TSharedPtr<FContactInfo> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	FContactInfo Info = *Item.Get();

	return
		SNew(STableRow< TSharedPtr<FContactInfo> >, OwnerTable)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			[
				SNew(STextBlock)
				.Font(FSlateFontInfo( FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 ))
				.Text(FText::FromString(Info.ContactName))

			]
			+ SHorizontalBox::Slot()
			[
				SNew(STextBlock)
				.Font(FSlateFontInfo( FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 ))
				.Text(FText::FromString(Info.ContactAddress))
			]
		];
}

void SContactWidget::CreateContactInfoList()
{
	ContactInfoList.Add(MakeShareable(new FContactInfo(TEXT("aaa"), TEXT("111"))));
	ContactInfoList.Add(MakeShareable(new FContactInfo(TEXT("bbb"), TEXT("222"))));
	ContactInfoList.Add(MakeShareable(new FContactInfo(TEXT("ccc"), TEXT("333"))));
	ContactInfoList.Add(MakeShareable(new FContactInfo(TEXT("ddd"), TEXT("444"))));
}

void SContactWidget::OnGetChildrenForQueryGroup(TSharedPtr<FQueryInfo> InItem, TArray<TSharedPtr<FQueryInfo> >& OutChildren)
{
	OutChildren = InItem->Children;
}

TSharedRef<ITableRow> SContactWidget::MakeQueryInfoWidget(TSharedPtr<struct FQueryInfo> InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (InItem->bIsGroup)
	{
		{
			return 			
				SNew(STableRow< TSharedPtr<FContactInfo> >, OwnerTable)
				[
					SNew(STextBlock)
					.Font(FSlateFontInfo( FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 ))
					.Text(FText::FromString(InItem->GroupName))

				];
		}
	}
	else
	{
		return
			SNew(STableRow< TSharedPtr<FContactInfo> >, OwnerTable)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Font(FSlateFontInfo( FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 ))
					.Text(FText::FromString(InItem->ContactName))

				]
				+ SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Font(FSlateFontInfo( FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 ))
					.Text(FText::FromString(InItem->ContactAddress))
				]

			];


	}

	//return 
	//	SNew(SQueryInfoWidget, OwnerTable)
	//		.Item(InItem);

}

void SContactWidget::CreateQueryInfoList()
{
	TSharedPtr<FQueryInfo> Group1 = MakeShareable(new FQueryInfo(true, TEXT("group1"), TEXT("0"), TEXT("0")));
	Group1->Children.Add(MakeShareable(new FQueryInfo(false, TEXT("none"), TEXT("aaa"), TEXT("111"))));
	Group1->Children.Add(MakeShareable(new FQueryInfo(false, TEXT("none"), TEXT("bbb"), TEXT("222"))));
	Group1->Children.Add(MakeShareable(new FQueryInfo(false, TEXT("none"), TEXT("ccc"), TEXT("333"))));
	QueryInfoList.Add(Group1);
	TSharedPtr<FQueryInfo> Group2 = MakeShareable(new FQueryInfo(true, TEXT("group2"), TEXT("0"), TEXT("0")));
	Group2->Children.Add(MakeShareable(new FQueryInfo(false, TEXT("none"),	TEXT("ddd"), TEXT("444"))));
	QueryInfoList.Add(Group2);

}

TSharedRef< SWidget > SQueryInfoWidget::GenerateWidgetForColumn(const FName& ColumnName)
{
	if (Item->bIsGroup)
	{
		if (ColumnName == SContactWidget::GroupColumnName)
		{
			return 				SNew(STextBlock)
				.Font(FSlateFontInfo( FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 ))
				.Text(FText::FromString(Item->GroupName));
		}
	}
	else
	{
		if (ColumnName == SContactWidget::NameColumnName)
		{
			return				SNew(STextBlock)
				.Font(FSlateFontInfo( FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 ))
				.Text(FText::FromString(Item->ContactName));
		}
		else if (ColumnName == SContactWidget::AddressColumnName)
		{
			return				SNew(STextBlock)
				.Font(FSlateFontInfo( FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14 ))
				.Text(FText::FromString(Item->ContactAddress));
		}
	}
	return SNullWidget::NullWidget;
}

void SQueryInfoWidget::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)
{
		Item = InArgs._Item;
	SMultiColumnTableRow< TSharedPtr<FQueryInfo> >::Construct(FSuperRowType::FArguments(), InOwnerTableView);
}
#undef LOCTEXT_NAMESPACE
