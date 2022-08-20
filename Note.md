# Problem

## games101作业关键分析

https://www.jianshu.com/p/04b1e8ffe95d
tbn fenxi
https://zhuanlan.zhihu.com/p/139593847
https://zhuanlan.zhihu.com/p/412555049

## 视察贴图原理

https://zhuanlan.zhihu.com/p/265317045

## glm/opengl是列存储模式

```c++
glm::mat4x4 modelMatrix = glm::translate(glm::identity<glm::mat4x4>(), { 0.5, 0, 0 });
std::cout << glm::to_string(modelMatrix) << std::endl;
//存储如下：
//mat4x4((1.000000, 0.000000, 0.000000, 0.000000),
//(0.000000, 1.000000, 0.000000, 0.000000),
//(0.000000, 0.000000, 1.000000, 0.000000),
//(0.500000, 0.000000, 0.000000, 1.000000))
```

## 判断点在三角形中

利用点P与三角形各个点连成线段，然后依次和每条边叉乘。如果符号均>0或者小于0那么就在三角形内。
值得注意的是，在右手坐标系下，>0一般是逆时针排列的点（正面）,<0(顺时针，反面)。假如叉乘结果有等于0的话，那么就在边上。

## 计算视图矩阵

## 计算观察矩阵

camera矩阵其实就是以某点为原点然后旋转的意思，不过它不用转为世界坐标系
通常以某点为原点然后旋转多少度可以转为
P1 = Mt(x)*Mr(x)*Mt(-x)*P0;
但是camera坐标空间是不用转为世界坐标系的，那么
p1 = Mr(x)*Mt(-eye)*p0;

1.正交化基向量组合成的矩阵可以看作旋转矩阵。
2.应用旋转矩阵的点相当于点在基向量的投影。

## 计算投影矩阵


透视投影
https://zhuanlan.zhihu.com/p/122411512
https://zhuanlan.zhihu.com/p/403259571

三个准则
1.近平面不变
2.远平面中心点不变
3.椎体的点压缩后在近平面能找到对应的点

## 计算重心坐标

https://blog.csdn.net/wangjiangrong/article/details/115326930

```c++3种几何意义
//1.面积之比 
//2.i*PA+j*PB+k*PC = 0; 
//3.i*A+j*B+k*C = P
```

## 透视校正插值

https://zhuanlan.zhihu.com/p/403259571
先从一条直线矫正开始，得到i/j = az/cz;
三条边依次矫正就可以了。

## 背面剔除

判断是否在三角形的时候，如果选择>0那么就是选择正面,<0选择反面。
面应该默认一个顶点排列方向，一般都是逆时针。ps.旋转角度也是逆时针。

## zbuffer

## msaa

## fsaa

## 反射/折射

## 相机

glm::lookAt，加入eye和center一样，那么返回的矩阵是mat(0)


## Blender normal

https://zhuanlan.zhihu.com/p/79583664?ivk_sa=1024320u