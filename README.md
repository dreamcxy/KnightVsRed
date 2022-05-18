# KnightVsRed

Developed with Unreal Engine 4

### 问题
-[ ] ue4 鼠标的release触发和键盘的release触发（见5.16）


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
  - 控制移动，但是轴控制似乎会导致人物一直滑下去，xaxis不清空，因此换成了按键控制
  - 蓝图都有个defaultroot样的东西，是个小球，用于标记原点，游戏里面会看不见，最好不要删除，
不然PaperFlipbook会作为root节点，这样加入的camera会变成它的子组件，在左右旋转flipbook的时候会跟着一起转，等于没效果
* 鼠标的release操作， 很有问题，鼠标只要不动，就一直是release状态， 无语。
* 垃圾ue4， 真的是小问题不断，我持续开了几小时，它的ui界面就不行了，菜单就没法正常稳定显示，一直会闪烁。

### 5.16开发记录
* 真麻烦， git pull下来的要让ue重编
* 很奇怪， 鼠标的release事件跟键盘的release事件的触发应该不是同一个机制，鼠标release事件会导致attack动画没法正常还原到idle，
会不间断触发attack， 不知道是ue4的play模式下窗口点击的问题，还是确实是机制问题, 先改成按键触发了
* 加入red的idle

### 5.17开发记录
* 之前的动画控制是由代码里面进行控制的， 产生了一个动画没有播完就进行状态切换的问题（这也应该有代码设置的，但我没找到对应api），改为用ue的动画状态机进行控制
  * 扯淡，ue的动画状态机我没找到支持这种序列帧切换的，还不如代码里面自己管理，扯淡

### 5.18开发记录
* 上一个帧没有播完，下一个帧就替换的问题，`OnFinishedPlaying` 这个方法没法解决，它面对的是不loop的动画，但是idle是loop状态的，意味着
要修改这个问题
  * 改了个寂寞， 要是刚开始就不管切换问题就好了