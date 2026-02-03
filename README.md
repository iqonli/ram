# R.I.P. Archive Manager

> 一款极具实用性、功能极其强大的压缩软件

## 重要提示

这只是个笑话。笑点解析请看文末。

本项目使用了TRAE。

## 导语

本项目使用[GNU General Public License v3.0](LICENSE)许可证。

本项目旨在彻底解决**压缩文件时，即使已经以最大程度压缩，文件体积仍然很大**这一历史性问题。为了降低压缩率到10%甚至1%，IQ Online Studio经过长达`57542400`秒的艰苦研究后隆重发布了一个具有改变世界和划时代意义的史诗级算法——R.I.P.算法。（注：由于IQ Online Studio条件艰苦，在研发R.I.P.算法时没有联网或与外界有任何接触，排除任何抄袭的可能，直接认为R.I.P.算法是IQ Online Studio自主研发的产物。）

>## R.I.P.算法
>
>### 英文：R.I.P. SuanFa (R.I.P., Rush In Peace)
>
>一种有损压缩算法，基于队列。有以下几种计算模式：
>
>- 精准模式（时间复杂度O(N^2)）
>```c++
>static std::vector<unsigned char> preciseMode(const std::vector<unsigned char>& data)
>{
>	if (data.empty())
>	{
>		return {0};
>	}
>	
>	std::vector<unsigned char> current = data;
>	
>	while (current.size() > 1)
>	{
>		std::vector<unsigned char> next;
>		
>		for (size_t i = 0; i < current.size() - 1; ++i)
>		{
> 			next.push_back(current[i] ^ current[i + 1]);
>		}
>		
>		current = next;
>	}
>	
>	return current;
>}
>```
>
>- 快速前压模式（时间复杂度O(N)）
>```c++
>static std::vector<unsigned char> fastFrontMode(const std::vector<unsigned char>& data)
>{
>	if (data.empty())
>	{
> 		return {0};
>	}
>	
>	std::vector<unsigned char> current = data;
>	
>	for (size_t i = 1; i < current.size(); ++i)
>	{
> 		current[0] ^= current[i];
>	}
>	
>	return {current[0]};
>}
>```
>
>- 快速后压模式（时间复杂度O(N)）
>```c++
>static std::vector<unsigned char> fastBackMode(const std::vector<unsigned char>& data)
>{
> 	if (data.empty())
> 	{
> 		return {0};
> 	}
>    	
> 	std::vector<unsigned char> current = data;
>    	
> 	for (size_t i = 0; i < current.size() - 1; ++i)
> 	{
> 		current.back() ^= current[i];
> 	}
>    	
> 	return {current.back()};
>}
>```
>
>- 极速天命模式（时间复杂度O(1)）
>```c++
>static std::vector<unsigned char> destinyMode(const std::vector<unsigned char>& data)
>{
> 	if (data.empty())
> 	{
> 		return {0};
> 	}
>    	
> 	std::random_device rd;
> 	std::mt19937 gen(rd());
> 	std::uniform_int_distribution<> distrib(0, data.size() - 1);
>    	
> 	return {data[distrib(gen)]};
>}



## 介绍

1. 程序功能
   - 使用深度定制的R.I.P.算法，支持算法的所有计算模式
   - 为了保持压缩文件的最大程度压缩，虽然文件大小为1B，但仅有两种不同文件内容，BIN分别为：`00000000`、`00000001`
   - 支持直接运行程序、命令行调用、右键菜单使用
   - 自研分卷压缩技术哈未曼编码（Hafuman Encode），无需字典或映射表，精准压缩到bit，可以设置分卷大小（Byte）或分卷数量
   - 压缩文件格式为`.raw`，即为`R.I.P. Archive Writefile`的首字母缩写
   - 分卷压缩文件格式为`.n.raw`，避免与`.z01`、`.part1.rar`、`.7z.001`等格式冲突
   - 支持压缩后自动永久强力粉碎原文件，该选项默认自动关闭
   - 该软件的压缩功能速度快，效果好，我们强烈建议您将珍贵的照片、视频、文档，以及各种学习资料、工作文件、娱乐影音、软件资源等进行R.I.P.压缩后并删除原文件！
2. 注意事项
   - 虽然压缩出来的文件仅有1B，但请不用担心，这是经过严谨的压缩算法精确计算得来的文件，只要进行适当的逆向计算，即可精准解压出原文件
   - 由于压缩文件的压缩率极低，导致文件解压的计算较为复杂，解压操作需耗费很长一段时间，如果想要使用压缩文件请尽早解压（单个压缩前体积为1GiB的`.raw`压缩文件的解压时间保守估计为`-2147483647`年）
   - 程序使用的R.I.P.算法本身具备极高的安全系数，无需压缩密码，也可以实现极好的加密效果，压缩文件基本不可能逆向破解，适用于高度敏感机密文件的压缩，以及各种安全系数要求极高的场景

## 安装与使用

1. 下载[release](https://github.com/iqonli/RAM/releases)版的zip文件

1. 解压后，将`ram.exe`所在目录添加到环境变量

   >您可以在拥有管理员权限的命令行中运行`rundll32 sysdm.cpl,EditEnvironmentVariables`以直接进入环境变量页面
1. 进入命令行，运行`ram`查看提示信息

## 命令行参数调用手册

`ram [-en [-mode [num]] [-part [-n num | -b byte | -kb kbyte | -mb mbyte | -gb gbyte | -tb tbyte | -pb pbyte | -zb zbyte]] [-autodel] file [-to file]] [-de file [-to path]]`

### ``[-en ...]`` 压缩模式

``[-mode [num]]`` 压缩模式选择，默认为0

- `num`=0 精准模式
- `num`=1 快速前压模式
- `num`=2 快速后压模式
- `num`=3 极速天命模式

``[-part [-n num | -b byte | -kb kbyte | -mb mbyte | -gb gbyte | -tb tbyte | -pb pbyte | -zb zbyte]]`` 分卷压缩模式选择，`num`为分卷数量，``byte``、``kbyte``、``mbyte``、``gbyte``、``tbyte``、``pbyte``、``zbyte``为单个分卷的大小
`[-autodel]` 压缩后自动永久强力粉碎原文件，默认关闭
`file` 待压缩文件/文件夹，支持多个，用逗号连接
``[-to file]`` 压缩到…文件，可以省略后缀，默认压缩到同目录下的``[待压缩文件夹名或该目录名].raw``

### ``[-de ...]`` 解压模式

``file`` 待解压文件，仅支持R.I.P. Archive Manager使用R.I.P.算法压缩的文件

``[-to path]`` 解压到…目录，默认解压到同目录下的``/[压缩文件名]``



## 设备配置要求

### 个人用户最低配置：

CPU: AMD Ryzen Threadripper 7980X3D

RAM: 256GB DDR6-8400

GPU: Nvidia GeForce RTX 5090 Ti 48GB Ultra OC

OS: Microsoft Windows 12 Pro for Workstations 26H2

### 企业用户最低配置：

CPU: AMD EPYC 9754

RAM: 2TB DDR5-5600 REG ECC

GPU: NVIDIA H100 80GB HBM3 × 4

OS: Microsoft Windows Server 2025 Datacenter

有事没事请加QQ群：743278470，你可以添加句子，报告错误，寻求帮助，骂人



```笑点解析
一款极具实用性、功能极其强大的压缩软件
>软件不具备任何实用性。

本项目旨在彻底解决**压缩文件时，即使已经以最大程度压缩，文件体积仍然很大**这一历史性问题。
>根本没解决。

IQ Online Studio经过长达`57542400`秒的艰苦研究后
>57542400秒即为666天。

隆重发布了一个具有改变世界和划时代意义的史诗级算法——R.I.P.算法
>又称文件火葬场算法。

直接认为R.I.P.算法是IQ Online Studio自主研发的产物
>可能：我想要说的前人们都说过了。

英文：R.I.P. SuanFa (R.I.P., Rush In Peace)
>SuanFa彰显三脚猫英文，Rush In Peace体现宁静中的混乱。

一种有损压缩算法
>不是有损，而是全损。嘉奖了。

精准模式
>太精准了。

使用深度定制的R.I.P.算法
>本就是IQ Online Studio的算法，根本不需要深度定制。

为了保持压缩文件的最大程度压缩，虽然文件大小为1B，但仅有两种不同文件内容
>“仅有”体现了1B体积之大。

自研分卷压缩技术哈未曼编码（Hafuman Encode）
>“致敬”经典算法哈夫曼（Haffman）。

压缩文件格式为`.raw`，即为`R.I.P. Archive Writefile`的首字母缩写
>raw意为原始，是一种无损图片文件的格式，这里用“无损”反串全损，令人忍俊不禁。

支持压缩后自动永久强力粉碎原文件，该选项默认自动开启
>深刻体现了文件火葬场的性质。

该软件的压缩功能速度快，效果好
>计算速度快，粉碎效果好。

这是经过严谨的压缩算法精确计算得来的文件，只要进行适当的逆向计算，即可精准解压出源文件
>算法是很严谨，但是适当的逆向计算实在难以找到，堪比猴子算法。

单个压缩前体积为1GiB的`.raw`压缩文件的解压时间保守估计为`-2147483647`年
>时间太大，甚至溢出了。

压缩文件基本不可能逆向破解
>自信点，把“基本”去了。解压都不行，还逆向破解呢。

适用于高度敏感机密文件的压缩，以及各种安全系数要求极高的场景
>推荐给间谍使用。
```



