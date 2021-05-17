#include <common.h>
#include <dt-structs.h>
#include <dm/device.h>
#include <dm/read.h>
#include <clk.h>

#define MRAM_CFG_LEN    8

struct can_priv {
    u32 base;
    u32 mram_base;
    struct clk hclk;
    struct clk cclk;
    u32 mram_config_vals[MRAM_CFG_LEN];
};

static int can_of_to_plat(struct udevice *dev)
{
    struct can_priv *priv = dev_get_priv(dev);
    fdt_addr_t addr;
    int ret;

    // ret = clk_get_by_name(dev, "hclk", &priv->hclk);
	// if (ret)
	// 	return ret;

    // ret = clk_get_by_name(dev, "cclk", &priv->cclk);
	// if (ret)
	// 	return ret;

    addr = (int)dev_read_addr_name(dev, "m_can");
	if (addr == FDT_ADDR_T_NONE)
		return -EINVAL;
	priv->base = (u32)addr;

    addr = (int)dev_read_addr_name(dev, "message_ram");
	if (addr == FDT_ADDR_T_NONE)
		return -EINVAL;
	priv->mram_base = (u32)addr;

    ret = dev_read_u32_array(dev, "bosch,mram-cfg", priv->mram_config_vals, MRAM_CFG_LEN);
    if(ret)
        return ret;
 
    return 0;
}

static int can_probe(struct udevice *dev)
{
    struct can_priv *priv = dev_get_priv(dev);
    printf("base-reg: %x\n",priv->base);
    printf("mram-reg: %x\n",priv->mram_base);
    printf("mram-cfg: %d %d %d %d %d %d %d %d\n",
            priv->mram_config_vals[0],
            priv->mram_config_vals[1],
            priv->mram_config_vals[2],
            priv->mram_config_vals[3],
            priv->mram_config_vals[4],
            priv->mram_config_vals[5],
            priv->mram_config_vals[6],
            priv->mram_config_vals[7]);

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
    .priv_auto      = sizeof(struct can_priv),
};
