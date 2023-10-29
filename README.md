# REGICIDE
### 原版游戏规则
网站: https://badgersfrommars.com/pages/learn-to-play-regicide

规则pdf: https://www.regicidegame.com/site_files/33132/upload_files/RegicideRulesA4.pdf?dl=1
### 未完成的工作
+ 整体工作
  + Board类的状态应该如何设置？伤害计算公式应该是怎样的？
+ Card类
  + 卡牌是否需要id
  + 如何实现原版那样的多boss衔接？
+ Deck类
+ Character类
  + 选择手牌（需要前端对接）
  + （每个子类需要）设置内部计数器，更新计数器（需要接受board类的所有状态作为参数）
  + 对deck的管理大概需要引用计数或使用smart pointer
  + 如何实现原版那样的多boss衔接？
+ Board类
  + 状态有哪些
  + 伤害怎样计算
  + 如何管理deck的数量（是否是下放到子类去自行实现，例如设置一个纯虚函数virtual void set_decks()=0;）
  + 造成伤害的函数
  + 受伤弃牌
  + 判断死亡，如何处置尸体（是否下放到子类去实现）
  + 选择出牌的目标（需要前端对接）
  + 更新计数器的函数
  + 如何实现原版那样的多boss衔接？
+ Battle类
  + 回合开始时该做什么？
  + 判断死亡的时候该干什么，怎样判断游戏结束（是否下放到子类实现）
+ 其他类
  + 啥都没干呢