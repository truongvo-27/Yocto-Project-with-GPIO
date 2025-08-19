#include <linux/module.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/of.h>

#define DRIVER_AUTHOR "Vo Truong"
#define DRIVER_DESC   "Raspberry Pi GPIO27 LED driver desciptor base"

static struct gpio_desc *gpio_led;

static int gpio27_probe(struct platform_device *pdev)
{
    struct device *dev = &pdev->dev;

    gpio_led = gpiod_get(dev, "led", GPIOD_OUT_LOW);
    if (IS_ERR(gpio_led))
    {
        dev_err(dev, "Failed to get GPIO\n");
        return PTR_ERR(gpio_led); 
    }

    gpiod_set_value(gpio_led, 1);

    pr_info("GPIO27 LED driver loaded - LED ON\n");
    return 0;
}

static int gpio27_remove(struct platform_device *pdev)
{
    gpiod_set_value(gpio_led, 0);
    gpiod_put(gpio_led);         

    pr_info("GPIO27 LED driver unloaded - LED OFF\n");
    return 0;
}

static const struct of_device_id gpio27_dt_ids[] = {
    { .compatible = "rpi,gpio27-led" },
    { }
};
MODULE_DEVICE_TABLE(of, gpio27_dt_ids);

static struct platform_driver gpio27_driver = 
{
    .probe  = gpio27_probe,
    .remove = gpio27_remove,
    .driver = 
    {
        .name = "gpio27-led",
        .of_match_table = of_match_ptr(gpio27_dt_ids),
        .owner = THIS_MODULE,
    },
};
module_platform_driver(gpio27_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION("1.0");