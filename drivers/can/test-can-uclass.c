#include <dm/uclass.h>

UCLASS_DRIVER(can-emul) = {
	.name		= "can_emul",
	.id		= UCLASS_CAN_EMUL,
};
