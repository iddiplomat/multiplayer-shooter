#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSOverheadWidget.generated.h"

class UTextBlock;

UCLASS()
class MULTIPLAYERSHOOTER_API UMSOverheadWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* DisplayText;
	
	void SetDisplayText(const FString& TextToDisplay);
	
	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRole(APawn* InPawn);
	
protected:
	virtual void NativeDestruct() override;
};
