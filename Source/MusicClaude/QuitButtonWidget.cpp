#include "QuitButtonWidget.h"
#include "Kismet/KismetSystemLibrary.h"

void UQuitButtonWidget::QuitGame()
{
    if (IsValid(GetOwningPlayer()))
    {
        UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("UQuitButtonWidget::QuitGame called before PlayerController was available."))
    }
}
