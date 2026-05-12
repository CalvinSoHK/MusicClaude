#include "BaseWidget.h"

void UBaseWidget::InitWidget_Implementation(USequencerData* InData, USequencerComponent* InComponent)
{
    SequencerData = InData;
    SequencerComponent = InComponent;
}
