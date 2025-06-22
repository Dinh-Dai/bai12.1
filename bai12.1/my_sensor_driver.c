#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>

struct my_sensor_data {
	int threshold;
};

static int my_sensor_probe(struct platform_device *pdev)
{
	struct my_sensor_data *data;
	struct device_node *np = pdev->dev.of_node;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	if (of_property_read_u32(np, "threshold", &data->threshold)) {
		dev_err(&pdev->dev, "Failed to read threshold\n");
		return -EINVAL;
	}

	dev_info(&pdev->dev, "My Sensor threshold = %d\n", data->threshold);

	platform_set_drvdata(pdev, data);
	return 0;
}

static int my_sensor_remove(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "My Sensor driver removed\n");
	return 0;
}

static const struct of_device_id my_sensor_of_match[] = {
	{ .compatible = "you,my-sensor", },
	{ }
};
MODULE_DEVICE_TABLE(of, my_sensor_of_match);

static struct platform_driver my_sensor_driver = {
	.driver = {
		.name = "my_sensor_driver",
		.of_match_table = my_sensor_of_match,
	},
	.probe = my_sensor_probe,
	.remove = my_sensor_remove,
};

module_platform_driver(my_sensor_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Con");
MODULE_DESCRIPTION("Simple Platform Driver with threshold");
