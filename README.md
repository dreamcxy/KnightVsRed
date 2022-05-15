# KnightVsRed

Developed with Unreal Engine 4


### 5.13开发记录
* ue上传github
    - 要是碰到项目奔溃一直打不开的情况，删掉多余的文件夹，只保留content、source、config，让ue4重新编译
    - GetOwner()这个函数拿到的是actor，放置在场景中的物体
    - GetOwner()->GetName() 无法在构造函数里面打印，会引起ue奔溃（https://forums.unrealengine.com/t/calling-method-getowner-getname-crash-editor/352829）
* 导入并支持切换knight的idle,running序列帧

### 5.15开发记录
* knightcontroller->knightcomponentcontroller用于组件管理 ，add knightcontroller 用于actor管理， 不然没有
办法监听输入事件（ue里面改个代码文件名称或者删除步骤真tm复杂，离谱）
* 从pawn生成KnightPawn管理knight
  - ue可以从c++直接生成一个actor，直接把代码拖入到场景里面即可，然后可以将它保存成一个蓝图，方便以后复用
  - ue一个坑人的地方在于，虽然你没有显示include相应的头文件，但是你编译代码仍然可以通过，但你的功能可能就会没有办法运行
  - 控制移动，但是轴控制似乎会导致人物一直滑下去，xaxis不清空

