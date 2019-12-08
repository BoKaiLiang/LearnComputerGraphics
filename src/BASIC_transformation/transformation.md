# Transformation

* 使用 [recp/cglm](https://github.com/recp/cglm) 對物件進行位移、旋轉、縮放。
## 使用
> 1. Build project using `cmake`.
> 2. Enter `./build/BASIC_transformation`.
> 3. Press `SPACE` to show the transformation.

## 向量與矩陣
* 注意矩陣相乘是由右至左。

* 位移
    * 在原始向量上加上另一個向量，而或得一个在不同位置的新向量的過程。
    * 位移矩陣: 
    $$\begin{bmatrix}
    1 & 0 & 0 & T_x\\
    0 & 1 & 0 & T_y\\
    0 & 0 & 1 & T_z\\
    0 & 0 & 0 & 1
    \end{bmatrix}
    \begin{pmatrix}
    x \\
    y \\
    z \\
    1
    \end{pmatrix} = 
    \begin{pmatrix}
    x + T_x \\
    y + T_y \\
    z + T_z\\
    1
    \end{pmatrix}$$
* 旋轉:
    * 旋轉函式上的角(Angle)大多是指弧度(Radian)
        * 弧度轉角度 : 

## 延伸資料
* [affine transformation](https://en.wikipedia.org/wiki/Affine_transformation)