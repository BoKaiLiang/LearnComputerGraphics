# Phong lighting model


## 實作流程

### Ambient lighting
* 翻譯為環境光，即使關閉所有光源仍然會有些許的光源對物體進行照射，例如: 月亮的光線

### Diffuse lighting
* 光照射的方向與角度會使物體產生不同的*顏色*，例如: 物體在背光面會是黑色 *(不會全黑到看不到，因為還有環境光)*

* 想要計算出該片段(Fragment)與光源所產生的漫射效果需要以下:
    * 法向量(Normal vector)
    * 光源的方向: `normal(light_pos - target_pos)`

    之後對兩向量的夾角進行 `點積`，若答案越接近1則表示光源越垂直於片段，效果越強，反之亦然。

### Specular lighting
* 例如金屬會產生的強光的反射效果。
* 欲求出強光的效果，類似於漫射的計算方式，這次需要
    * 視角對片段的向量
    * 光線對物體的反射向量

    然後進行`點積`，對產生的數字進行指數的疊加。

## 注意
* 在實作光照模型時，大多不需要光的向量大小，而是方向。
* 點積運算的時候，若角度大於`90`則會產生負值。
* 在物體進行非等比放大時，頂點的法向量會產生變化。則需要  `Normal matrix`
    * [數學分析](http://www.lighthouse3d.com/tutorials/glsl-12-tutorial/the-normal-matrix/)

#### impl
- 直接拿`LIGHT_color`來改
- 主要改shader
- 兩種模式
   - 物體會放大/縮小
   - 燈會繞