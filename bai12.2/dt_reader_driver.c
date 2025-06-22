#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>

static int dt_reader_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	u32 my_val, child_val, my_array[3], size;
	const char *my_name, *child_name;
	const __be32 *reg_prop;
	struct device_node *child;
	u64 child_addr, child_size;

	dev_info(&pdev->dev, "dt_reader_probe called\n");

	if (!of_property_read_u32(np, "my-val", &my_val))
		dev_info(&pdev->dev, "my-val = %u\n", my_val);

	if (!of_property_read_string(np, "my-name", &my_name))
		dev_info(&pdev->dev, "my-name = %s\n", my_name);

	if (!of_property_read_u32_array(np, "my-array", my_array, 3))
		dev_info(&pdev->dev, "my-array = <%u %u %u>\n",
		         my_array[0], my_array[1], my_array[2]);

	child = of_get_child_by_name(np, "child@1");
	if (!child) {
		dev_err(&pdev->dev, "Cannot find child@1 node\n");
		return -ENODEV;
	}

	if (!of_property_read_u32(child, "child-val", &child_val))
		dev_info(&pdev->dev, "child-val = %u\n", child_val);

	if (!of_property_read_string(child, "child-name", &child_name))
		dev_info(&pdev->dev, "child-name = %s\n", child_name);

	if (!of_property_read_u32(child, "my-val", &my_val))
		dev_info(&pdev->dev, "my-val (overridden in child) = %u\n", my_val);

	reg_prop = of_get_property(child, "reg", &size);
	if (reg_prop && size >= 8) {
		child_addr = of_read_number(reg_prop, 1);
		child_size = of_read_number(reg_prop + 1, 1);
		dev_info(&pdev->dev,
		         "child reg addr = 0x%llx, size = 0x%llx\n",
		         (unsigned long long)child_addr,
		         (unsigned long long)child_size);
	}

	return 0;
}

static int dt_reader_remove(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "dt_reader_driver removed\n");
	return 0;
}

static const struct of_device_id dt_reader_of_match[] = {
	{ .compatible = "mycompany,mydevice" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, dt_reader_of_match);

static struct platform_driver dt_reader_driver = {
	.probe  = dt_reader_probe,
	.remove = dt_reader_remove,
	.driver = {
		.name = "dt_reader_driver",
		.of_match_table = dt_reader_of_match,
	},
};

module_platform_driver(dt_reader_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Platform driver to read properties from device tree");

