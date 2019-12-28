# Render line

*如何不使用Grphics API (OpenGL/DirectX) 劃出一條線 ?*

## Bresenham's line algorithm
* 利用斜率，由點a畫至點b。
* 最簡單的直線光柵化演算法。

#### 注意: 最基本的演算法會出現兩個問題，一個是當斜率是負的，另一個是線反著畫(右上到左下)

## Sampling

#### Bresenham的問題:
1. 不能控制直線寬度。
2. 座標為整數。
3. 只能用單色寫入一個顏色，只用單色會有嚴重的鋸齒效果。

### Super sampling

## SDF

### Use AABB optimize SDF

### 額外問題: 如何read和write各式的圖片檔(jpg、png、bmp、tga、gif)?

## Resources
* [用 C 语言画直线](https://zhuanlan.zhihu.com/p/30553006)
* [Wiki](https://zh.wikipedia.org/wiki/%E5%B8%83%E9%9B%B7%E6%A3%AE%E6%BC%A2%E5%A7%86%E7%9B%B4%E7%B7%9A%E6%BC%94%E7%AE%97%E6%B3%95)