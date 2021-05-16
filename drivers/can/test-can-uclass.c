#include <dm/uclass.h>

UCLASS_DRIVER(can_emul) = {
	.name		= "can_emul",
	.id		= UCLASS_CAN_EMUL,
};
