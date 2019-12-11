# FPS Camera

## 如何製造一個自由視角的攝像機?
> 一個物體投影在螢幕上，會經過 Local space、World space、View(Eye) space、Clip space。攝影機的處理就是在View space上。

1. 設想一個"自由"視角的攝影機需要甚麼操作?
    * 六個方向的移動(上、下、左、右、前、後)
    * 視角的放大與縮小
    * 旋轉視角

2. 對應以上需求，可以有甚麼作法
    * 方向的移動: 對相機進行**位移**
    * 視角放大縮小: 修改對於Clip space的`perspective`函數的fov參數，fov參數可以對*frustrum*的`zNear`、`zFar`進行調整。
    * 視角旋轉: 參考[歐拉角](https://learnopengl.com/Getting-started/Camera)

#### 歐拉角會產生Gimbal lock，於此同時，會使用**四元數**進行完善。

## `Look At` 矩陣
* [請參考這篇](http://www.songho.ca/opengl/gl_camera.html#lookat)

## 延伸資料
* [四元數(Quaternions)](https://github.com/cybercser/OpenGL_3_3_Tutorial_Translation/blob/master/Tutorial%2017%20Rotations.md)

## 待解決問題
* 高效能的數學函式庫，使用`cglm`進行的相機位移會產生移動的殘影。