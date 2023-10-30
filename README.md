# REGICIDE
### 原版游戏规则
网站: https://badgersfrommars.com/pages/learn-to-play-regicide

规则pdf: https://www.regicidegame.com/site_files/33132/upload_files/RegicideRulesA4.pdf?dl=1
### 未完成的工作
+ 整体工作
  + 如何实现原版那样的多boss衔接？
+ Card类
  + 卡牌是否需要id
+ Deck类
+ Character类
  + 选择手牌（需要前端对接）
  + （每个子类需要）设置内部计数器，更新计数器（需要接受board类的所有状态作为参数）
  + 对deck的管理大概需要引用计数或使用smart pointer
+ Board类
  + 判断死亡，如何处置尸体（是否下放到子类去实现）
  + 选择出牌的目标（需要前端对接）
  + 更新计数器的函数
+ Battle类
  + 判断死亡的时候该干什么，怎样判断游戏结束（是否下放到子类实现）
+ 其他类
  + 啥都没干呢