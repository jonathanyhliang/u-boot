
#include <common.h>
#include <dm.h>
#include <dm-demo.h>
#include <errno.h>
#include <fdtdec.h>
#include <log.h>
#include <malloc.h>
#include <asm/io.h>
#include <linux/list.h>

UCLASS_DRIVER(demo) = {
	.name		= "can",
	.id		= UCLASS_CAN,
};
