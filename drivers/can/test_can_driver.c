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
    struct can_plat *plat = dev_get_plat(dev);
    const void *blob = gd->fdt_blob;
    int node = dev_of_offset(dev);
    if(fdtdec_get_int_array(blob, node, "bosch,mram-cfg", plat->mram_config_vals, MRAM_CFG_LEN)) {
        return -EINVAL;
    }

    return 0;
}

static int can_probe(struct udevice *dev)
{
    struct can_plat *plat = dev_get_plat(dev);
    printf("mram-cfg: %d %d %d %d %d %d %d %d\n",
            plat->mram_config_vals[0],
            plat->mram_config_vals[1],
            plat->mram_config_vals[2],
            plat->mram_config_vals[3],
            plat->mram_config_vals[4],
            plat->mram_config_vals[5],
            plat->mram_config_vals[6],
            plat->mram_config_vals[7]);

    return 0;
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
