# Problem

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

## 计算重心坐标

[https://blog.csdn.net/wangjiangrong/article/details/115326930]
```c++3种几何意义
//1.面积之比 
//2.i*PA+j*PB+k*PC = 0; 
//3.i*A+j*B+k*C = P
```

## 透视校正插值

## zbuffer

## msaa

## fsaa