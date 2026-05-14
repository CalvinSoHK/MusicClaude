#include "QuitButtonWidget.h"
#include "Kismet/KismetSystemLibrary.h"

void UQuitButtonWidget::QuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}
