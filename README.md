# KnightVsRed

Developed with Unreal Engine 4

### 问题
-[ ] ue4 鼠标的release触发和键盘的release触发（见5.16）
-[ ] ue4 paperflipbook动画切换问题（见5.18， 5.17）

### 参考文档
- [collision官方文档](https://docs.unrealengine.com/4.27/zh-CN/InteractiveExperiences/Physics/Collision/Reference/)
- [box collision 详细开发记录](https://zhuanlan.zhihu.com/p/26965666)
- [附加组件的问题](https://blog.csdn.net/jfengsky/article/details/109271706)、[组件参考](https://www.cnblogs.com/wodehao0808/p/8109463.html)
- [碰撞检测](https://its201.com/article/niu2212035673/82716828、https://zhuanlan.zhihu.com/p/26965666)
- [GameMode和GameState文档](https://docs.unrealengine.com/4.26/zh-CN/InteractiveExperiences/Framework/GameMode/)
- [加载资源](https://www.cnblogs.com/KillerAery/p/12031057.html)
- [不用锁保证线程安全](https://blog.csdn.net/shyjhyp11/article/details/112143907)
- [linux 下守护进程](https://segmentfault.com/a/1190000022770900)
- [一些或许可以用的C++log库](https://www.zhihu.com/question/37640953)

### 被ue4气死的问题
- bindFunc不做函数名检测，全靠自觉
- 构造函数只适合做资源加载，其他的别放进去
- ue4 删除代码太麻烦了， 有些代码文件虽然不用了，但也没删除

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

### 5.20开发记录
* 先把动画调整回原来的5.16的版本
* 攻击判定，目前采用的这么个方法
  * 按键0.01s之后，激活attackRange，判定对方在不在range范围之内
  * 游戏之后，按~，输入show Collision 可以看到collision范围, 或者设置hiddenInGame为false即可
  * boxcomponent改为动态生成，避免手动添加的component与knight的方向相反range（16,0,19）
    * 离谱，离谱，离谱 ue4 为什么这么容易崩溃，
    你的component是没有办法在非构造函数里面生成的嘛？？离谱， `CreateDefaultSubobject`这个函数只能在构造函数里面调用，太tm离谱了
    可以，碰到一个同样蛋疼的老哥（https://blog.csdn.net/lqpgfz/article/details/47041261）
    * 离谱，knight_blueprint本身是没有collision的，需要自己添加

### 5.23 开发记录
* 正常，周末两天一点没动，无语
* 添加collision检测，[collision官方文档](https://docs.unrealengine.com/4.27/zh-CN/InteractiveExperiences/Physics/Collision/Reference/)
* ue4 里面获取component，调用到Cast函数的，不要放到构造函数里面，极其容易崩溃
* 不手动添加collision component 是没法通过show collision展示出来的

### 5.28 开发记录
* [box collision 详细开发记录](https://zhuanlan.zhihu.com/p/26965666)
* `CreateDefaultSubobject` 这个函数绝对有问题，我调用的地方都会崩溃
* [附加组件的问题](https://blog.csdn.net/jfengsky/article/details/109271706)、[组件参考]（https://www.cnblogs.com/wodehao0808/p/8109463.html）
* 服，不太懂ue4 `BindFunction`为什么不做函数名字检测，我tm绑了一个错误的函数名，我还一直在看其他地方的问题，没搞懂，既然你要我输入名字字符串，那你tm好歹做个名字检测啊，
不然有个屁用，我tm还一直以为是collision组件的问题（日常被ue4气死）
* 调整5.20的思路，将attackRange在蓝图中一开始就创建好，附着为PaperFlip的子component，就能解决方向不对的问题
* paperClip 本身带有一个碰撞，得预先关掉，不然attackRange会跟它之间发生碰撞
* 开始做整个游戏的manager, 看样子是要引入GameMode了

### 5.30 开发记录
* worldSettings下面调整默认的GameMode，项目会默认创建一个`KnightVsRedGameModeBase`, 不需要额外创建
* Couldn't spawn player: Failed to spawn player controller, GameSession is null 使用了GameMode，如果不指定那几个必须的类，就会出现这些问题

### 6.16 开发记录

-  前几天一直有琐事缠着，没能推进，今天开始继续推进
- 开始部署server端代码，公司连接外部开发机是真的卡顿，只能先在开发机上部署，到时同步到腾讯云上面去了
- 线程安全的继承单例（[不用锁保证线程安全](https://blog.csdn.net/shyjhyp11/article/details/112143907)）
- 提交一些template

### 6.19 开发记录

- servertemplate 添加mainloop

### 6.20 开发记录

- 提交gametime
- 基础架构的建设确实枯燥，但很有意思，并没有ddl，逐步了解每一个地方
- 调研log， 感觉上可能还是要自己实现一个[log](https://www.zhihu.com/question/37640953)