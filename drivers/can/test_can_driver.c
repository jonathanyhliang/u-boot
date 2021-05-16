#include <common.h>
#include <dt-structs.h>
#include <dm/device.h>

#define MRAM_CFG_LEN    8

struct can_plat {
#if CONFIG_IS_ENABLED(OF_PLATDATA)
    struct dtd_can dtplat;
#endif
    u32 mram_config_vals[MRAM_CFG_LEN];
};

static int can_of_to_plat(struct udevice *dev)
{
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
    struct can_plat *plat = dev_get_plat(dev);
    const void *blob = gd->fdt_blob;
    int node = dev_of_offset(dev);
    if(fdtdec_get_int_array(blob, node, "bosch,mram-cfg", plat->mram_config_vals, MRAM_CFG_LEN)) {
        return -EINVAL;          
    }
#endif

    return 0;
};

static int can_probe(struct udevice *dev)
{
    struct can_plat *plat = dev_get_plat(dev);

#if CONFIG_IS_ENABLED(OF_PLATDATA)
    struct dtd_can *dtplat = &plat->dtplat;
    memcpy((u32)plat->mram_config_vals, dtplat->bosch_mram_cfg, MRAM_CFG_LEN);
#endif
    printf("can probe\n");
}

static const struct udevice_id can_of_match[] = {
    { .compatible = "bosch,m_can" },
    {}
};

U_BOOT_DRIVER(can_drv_emul) = {
    .name           = "can_drv_emul",
    .id             = UCLASS_CAN_EMUL,
    .of_match       = can_of_match,
    .of_to_plat     = can_of_to_plat,
    .probe          = can_probe,
    .plat_auto      = sizeof(struct can_plat),
};
