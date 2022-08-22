# KnightVsRed

Developed with Unreal Engine 4

### 问题
- [ ] ue4 鼠标的release触发和键盘的release触发（见5.16）

- [ ] ue4 paperflipbook动画切换问题（见5.18， 5.17）

- [ ] rpc这个用法还没有尝试过 

- [ ] 宏里面遍历不定参数

- [x] c++的multidefine的编译问题

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
- [无锁队列1](https://www.stubbornhuang.com/796/)、 [无锁队列2](https://blog.51cto.com/quantfabric/2588193)
- [服务端架构模型](https://github.com/balloonwj/CppGuide/blob/master/articles/%E6%B8%B8%E6%88%8F%E5%BC%80%E5%8F%91%E4%B8%93%E9%A2%98/12%E7%BB%8F%E5%85%B8%E6%B8%B8%E6%88%8F%E6%9C%8D%E5%8A%A1%E5%99%A8%E7%AB%AF%E6%9E%B6%E6%9E%84%E6%A6%82%E8%BF%B0.md)
- [无锁编程](https://www.cnblogs.com/gaochundong/p/lock_free_programming.html)
- [关于c++模板声明和定义拆分开的问题](https://www.zhihu.com/question/20630104)
- [关于epoll监听关闭的问题](https://www.zhihu.com/question/289965746)
- [网络通讯使用char](https://www.zhihu.com/question/361487567)、[针对string的优化思路](https://codeantenna.com/a/f44gKMl0Ra)
- [raii 和 scopreguard](https://www.cnblogs.com/chenny7/p/11990105.html)、 [raii 模板化](https://ld246.com/article/1524705073004)
- [gtest做单元测试](https://simonzgx.github.io/2020/06/07/%E4%BD%BF%E7%94%A8googletest%E5%81%9A%E5%8D%95%E5%85%83%E6%B5%8B%E8%AF%95/) 、 [gtest做单元测试](https://gohalo.me/post/cpp-gtest-unit-test-usage.html)
- [magic_enum](https://github.com/Neargye/magic_enum)、[实现enum到string的方法](https://belaycpp.com/2021/08/24/best-ways-to-convert-an-enum-to-a-string/)、[宏里面遍历不定参数](https://www.itranslater.com/qa/details/2326168829484860416)
- [c++ 高效拷贝文件的方法](https://stackoverflow.com/questions/10195343/copy-a-file-in-a-sane-safe-and-efficient-way)

### 开发中想死的瞬间
- bindFunc不做函数名检测，全靠自觉
- 构造函数只适合做资源加载，其他的别放进去
- ue4 删除代码太麻烦了， 有些代码文件虽然不用了，但也没删除
- 右手大拇指受伤了，按不了空格键，改为左手大拇指
- c++ 很强大， 过于强大

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

### 6.21 开发记录

- 引入epoll
- 包装socket

### 6.22 开发记录

- 服务端框架梳理，最后选择采用异步-固定多线程，单进程内部有多个不同责任的子线程，线程与线程之间通过无锁队列通信
- 引入无锁队列，引入了kfifo，幸好我只是在linux上的服务器，要考虑跨平台，跨编译器啥的可真是太复杂了
- kfifo的开发并没有使用之前包装成类的做法，仿照linux，kfifo属性包装成struct， 但是具体的操作函数并没有放在struct里面，而是作为普通函数在同一个namespace下面

### 6.23 开发记录

- 开发进度有点慢，虽然每天都有提交，但有时候只是写了个函数名就提交了，真的是文件夹建好了
- 测试kfifo，逐步开始对现有代码进行编译
- 梦回刚入职的时候，写epoll用例的时候，不过那时候真的是照抄

### 6.24 开发记录

- 容我划一天水

### 6.28 开发记录

- 最近有点沉迷帝国时代，开发缓慢
- 工作上python也实现了一套类似的，不得不说python的开发速度还是要比c++快的
- 每次用c++从0开始写框架真的要哭，不愧是军工箱，真的是粗糙，还得不断看别人代码，才能知道怎么设计最好，并且最蛋疼的是，因为很多库要支持跨平台，代码写的真的是复杂的一笔，甚至有些引用了其他人的库，比如boost， 头痛
- python用就用了第三方了， 安装配置都要比c++容易的多，并且更加没有负罪感，c++要是用了就感觉，底层还在用，要你做什么
- c++的每一处的设计都得从设计图开始，不然最后很容易理不清关系

### 6.30 开发记录

- log日志，以及日志配置化，说的容易
- md, 昨天的开发忘记提交了，少了一个绿点

### 7.1 开发记录

- 继续log日志开发
- 将各种buffer拆分开，原本charbuffer，和 fifobuffer都是baseBuffer的继承类，现在改为，handler<Buffer>的形式，利用萃取统一charBuff和fifoBuffer的接口。
- logger.h , handler.h, buffer.h 相互独立开来
- 还是需要引入单元测试

### 7.8 开发记录

- 其实epoll监听关闭还是不是那么靠谱，靠谱点的做法还是要靠双端的心跳来维持
- 最近的开发是在python上的， 就没有在这个地方同步进度

### 7.9 开发记录

- ctrl+c直接停止的是main进程，里面的循环没有停止的话， 是没有办法停止的

### 7.12 开发记录

-  char* 、char[] 和 string各有优劣，在涉及网络传输的时候不要用string，其他时候，其实用string也无妨， 但string的查找效率会很慢

### 7.27 开发记录

- 用来做资源管理的不仅有raii，还有一个scopeguard用法

### 7.29 开发记录

- 引入gtest做单元测试、编译问题真的好麻烦啊，花了两个小时终于成功了， 将CMakeLists区分开来，按照不同模块进行编译了

- 把开发环境从服务器迁移到wsl了， 确实迁移过来之后方便了很多

- 不行， 之前7.1设计的用法不合适， 改回原来的父类继承的做法

  - 一个原因是 这种写法太过丑陋和复杂

    `

    ```
    std::unique_ptr<SLog<FileHandler<CharLogBuffer>>> pstLog(new SLog<FileHandler<CharLogBuffer>>);`
    ```
    
  - 另一个原因是，调用模板，有好多坑啊

### 7.31 开发记录

- 初步编译通过

### 8.1 开发记录

- 调整枚举值到string的写法， 从switch修改到宏定义，有个叫magic_enum的， 不过它是基于c++17的， 但我要做的没有那么复杂，试着在c++14上面实现类似的
- 但后续发现，magic_enum里面使用到的`__PRETTY_FUNCTION__`并不是在所有的编译情况下都能返回正确的所有的格式，因此放弃使用这个方案。
- 最终因为不想引入boost，还是选择了下面这个方案（不同的方案比较可以见参考文档的 实现enum到string的方法 这个一条）
- ```c++
  #include <iostream>
   
  #define ENUM_MACRO(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10)\
      enum class name { v1, v2, v3, v4, v5, v6, v7, v8, v9, v10 };\
      const char *name##Strings[] = { #v1, #v2, #v3, #v4, #v5, #v6, #v7, #v8, #v9, #v10};\
      template<typename T>\
      constexpr const char *name##ToString(T value) { return name##Strings[static_cast<int>(value)]; }
   
  ENUM_MACRO(Esper, Unu, Du, Tri, Kvar, Kvin, Ses, Sep, Ok, Naux, Dek);
   
  int main()
  {
      std::cout << EsperToString(Esper::Kvin) << std::endl;
  }
  ```

- enum 和 enum class还是有些区别的， 这个我之前竟然不知道。

### 8.2 开发记录

- 7.1 ， 在原来的基础上能调通了，但后续还是会放弃这个设计，不合理
- 出现很多undefined问题，根本在于common模块没有编译，所以要添加编译
- multidefine的时候，甚至加了个static就好了， c++的编译也太tm奇怪了，clion也太好用了

### 	8.3 开发记录

- 指针统一用智能指针进行管理
- 添加buffer部分的逻辑



### 8.7 开发记录

- 统一之前的file处理函数

### 8.8 开发记录

- 添加一些file处理函数

### 8.9 开发记录

-  `vector<char*>` 要注意 `char*`指针指向的是同一块地址

  ```c++
  while ((diread = readdir(dir)) != nullptr)
          {
              if (strcmp(diread->d_name, ".") == 0 || strcmp(diread->d_name, "..") == 0)
              {
                  continue;
              }
              if (pszFilePrefix != nullptr)
              {
                  // 判断文件前缀是否跟pszFilePrefix相同
                  if (strstr(diread->d_name, pszFilePrefix) == nullptr)
                  {
                      continue;
                  }
              }
  //            vecFiles.push_back(diread->d_name);
              char szFilePath[MAX_LOG_FILE_PATH_SIZE];
              sprintf(szFilePath, "%s/%s", pszDirName, diread->d_name);
              vecFiles.push_back(szFilePath);
          }
  ```

  这段代码里面的`vecFiles` 里面存储的`szFilePath`就一直是同一个地址， 很奇怪。

- 谨慎的返回一个string的`c_str()`, 因为`c_str()`指向的是string内部的缓冲区的指针，要是string析构了， 那么这个指针指向的也就是不知道的内容了

- 添加了rotatingfiletimehandler

- 为了能够利用宏的形式调用SLog， Log函数必须是个static函数，导致SLog里面其他函数和变量都必须是static的，不然Log函数是没有办法调用的。

- 包装成宏

###  8.10 开发记录

- 添加homeserver



### 8.22 开发记录

- 没想到一下子又停了这么久
- homeserver参加编译，很奇怪， 明明是支持posix的， 但clion的编译会提示找不到
