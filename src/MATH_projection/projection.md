# Projection

* 在OpenGL中3D視角。

## 使用
> 1. Build project by `build.bat`.
> 2. Enter `./build/MATH_projection`.

### 問題#1: 甚麼是NDC?

* Normalized Device Coordinate, NDC
* 每個頂點的x，y，z坐標都應該在-1.0到1.0之間，超出這個坐標範圍的頂點都將不可見。我們通常會自己設定一個坐標的範圍，之後再在頂點著色器中將這些坐標變換為標準化設備坐標。然後將這些標準化設備坐標傳入光柵器(Rasterizer)，將它們變換為屏幕上的二維坐標或像素。 - *from learnopengl CN*

* [Learn Opengl - Coordinate Systems](https://learnopengl.com/Getting-started/Coordinate-Systems)

### 問題#2: 如何產生3D視角的?
* 一個頂點將依序經過以下空間(矩陣)變換
    * Local space: 表示物體最開始的位置。
    * World space: 如同字面上的意思，該物體對於該世界的座標。
    * View space: 又稱Eye space，可以想像成我們的視角觀察該物體的相對位置。
    * Clip space: 想像有一個*觀察箱*，我們只能看到箱內的的東西，箱內以外的部分我們看不到，所以才稱為剪裁(Clipped)空間。
        * 觀察箱被稱為***平截頭體(Frustrum)***
        * 在Clip space的投影矩陣又分為兩種，**透視(Perspective)**和**正視(Orthogonal)**。

## 延伸資料
