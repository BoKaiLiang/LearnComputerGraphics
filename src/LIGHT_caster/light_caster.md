# Light Caster

**注意: 進行光線的運算，大多只需要光的方向而不是大小(magnititude)**

## 投射種類

### 平行光 (Directional light)
* 一個光源在**近似無限遠**的地方，例如: 太陽就可以視為平行光

### 點光源 (Point light)
* 光源在World space的某一處，光亮會隨在距離而衰減。

#### 衰減

``` light_dis = light_str / (constant + linear * d + exp * d * d)```

* 解釋: 
    * `light_dis`為光在`d`距離衰減後的亮度， `light_str`為光原始的亮度(強度)
    * `constant`、`linear`、`exp`皆為常數係數。
    * 該公式遵守[平方反比定律-inverse square law](http://hyperphysics.phy-astr.gsu.edu/hbase/Forces/isq.html) ，所以按照上面的定律，公式會成為: ```light_dis = light_dir / d * d``` ，但以上公式有幾個問題，像是距離越小，光的亮度會趨近無限大，沒有很好的效果曲線等。
    * 修改後的公式，利用以下的參考1把`constant`設為`1.0`，可以讓光的強度不會因為距離而趨近無限大。


* [衰減公式參考-1](http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation)
 [衰減公式參考-2](http://ogldev.atspace.co.uk/www/tutorial20/tutorial20.html)



### 聚光 (Spot light)
* 光源特定指向某一個方向，只有在特定半徑內物體才會被照亮，例如: 手電筒。

* 需要**光的位置向量(光的方向向量)**、**光照射的方向**、**切光角(cut off)**

**注意:**
    * `cosine`的運算越接近90度數字越小，0度則為1.0。

* [聚光燈計算](https://learnopengl.com/Lighting/Light-casters)