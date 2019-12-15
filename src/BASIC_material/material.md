# Material

## Texture, Shader and Material
* 可以簡單地表示: **Material = Texture + Shader**
    * Texture翻譯成材質貼圖或紋理貼圖，顧名思義，Texture就是機器人身上的貼圖。
    * Shader中文翻譯作"著色器"(不是很喜歡這翻譯)，是運作在GPU上的一支程式，它利用定義的屬性及貼圖來"告訴"GPU"要怎麼畫"我們的機器人
    * Material譯作材質，以程式的角度來看，其實就是Texture與Shader的集合


#### impl
* 修改(組織)shader
    * `struct Material`, `struct light`