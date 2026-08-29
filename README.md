# Texas Hold'em Desktop — 德州扑克游戏源码|德州扑克游戏源码|德州俱乐部源码|德州源码


[English](README.en.md) | [繁體中文](README.zh-TW.md) | [GitHub Pages](https://deepseek7878.github.io/texas-holdem-desktop/)
**·ALLIN德州扑克源码 ·八个德州玩法，远超市场主流德州玩法**


**简体中文 · 繁體中文 · English· 韩文· 马来文· 日文· 泰文· 印尼语·越南文**


# Texas Hold'em Desktop

[![GitHub stars](https://img.shields.io/github/stars/deepseek7878/texas-holdem-desktop?style=for-the-badge)](https://github.com/deepseek7878/texas-holdem-desktop)
[![GitHub downloads](https://img.shields.io/github/downloads/deepseek7878/texas-holdem-desktop/total?style=for-the-badge)](https://github.com/deepseek7878/texas-holdem-desktop/releases)
[![GitHub issues](https://img.shields.io/github/issues/deepseek7878/texas-holdem-desktop?style=for-the-badge)](https://github.com/deepseek7878/texas-holdem-desktop/issues)
[![License](https://img.shields.io/github/license/deepseek7878/texas-holdem-desktop?style=for-the-badge)](https://github.com/deepseek7878/texas-holdem-desktop/blob/main/LICENSE)

**俱乐部+联盟+私人局 | 10+种玩法 | **  
单人练习、锦标赛、手牌历史、数据分析、主题自定义、离线娱乐 / 單人練習、錦標賽、手牌歷史、數據分析、主題自訂、離線娛樂.
## 核心关键词

- 德州扑克桌面游戏源码
- 德州扑克源码
- 德州源码
- 德扑源码
- Texas Hold'em Desktop Game
- Texas Hold'em Poker Source Code
- Poker Desktop Game Source Code
- Offline Poker Game
- AI Poker Opponents
- Poker Tournament System
- 德州俱乐部源码
- 德州扑克多语言版本

## 核心功能

| 模块 | 功能 |
|---|---|
| 桌面客户端 | Windows、macOS、Linux 跨平台运行 |
| 游戏模式 | 单人练习、快速对战、挑战赛、锦标赛、朋友局 |
| AI 对手 | 离线 AI 玩家、难度等级、策略模拟 |
| 牌局流程 | Pre-flop、Flop、Turn、River、Showdown |
| 数据统计 | VPIP、PFR、3-bet、胜率、位置胜率、下注热图 |
| 手牌历史 | 牌局记录、回放、导出 CSV/JSON |
| 赛事系统 | 盲注升级、报名、淘汰、排名、积分榜 |
| 主题系统 | 夜间模式、经典模式、赌场风格、自定义配色 |
| 多语言 | 简体中文、繁体中文、英文、韩文、马来文等可扩展 |
| 打包发布 | Electron Builder、PyInstaller、Unity/C++ 客户端可扩展 |
## 🎮 一键下载运行 / Download & Play / 一鍵下載運行

[![Windows](https://img.shields.io/badge/Windows-Setup.exe-blue?style=for-the-badge&logo=windows)](https://github.com/deepseek7878/texas-holdem-desktop/releases/latest/download/TexasHoldem-Windows.exe)
[![macOS](https://img.shields.io/badge/macOS-DMG-orange?style=for-the-badge&logo=apple)](https://github.com/deepseek7878/texas-holdem-desktop/releases/latest/download/TexasHoldem-macOS.dmg)
[![Linux](https://img.shields.io/badge/Linux-AppImage-green?style=for-the-badge&logo=linux)](https://github.com/deepseek7878/texas-holdem-desktop/releases/latest/download/TexasHoldem-Linux.AppImage)

**解压即玩，无需安装！ / Extract and play! / 解壓即玩！**

## 🚀 三十秒上手 / 30s Quick Start / 30秒上手

```bash
# 方法1: 直接下载运行
# Win: TexasHoldem.exe → 双击
# Mac: TexasHoldem.app → 拖入Applications  
# Linux: ./TexasHoldem.AppImage

# 方法2: 源码运行
git clone https://github.com/deepseek7878/texas-holdem-desktop.git
cd texas-holdem-desktop
npm install && npm start  # Electron版
# 或
pip install -r requirements.txt && python main.py  # Python版
```

---

## 📱 核心功能展示 / Core Features / 核心功能展示

### **🎯 游戏模式**
| 模式 | 玩家数 | 特色 |
|------|--------|------|
| **练习桌** | 2-9人 | 随时暂停，盲注自定义 |
| **锦标赛** | 9人淘汰 | 盲注递增，实时排行 |
| **快速对战** | 6人桌 | 固定盲注，快速开局 |
| **挑战赛** | 单桌 | 限时决策，计分制 |

### **📊 数据系统**
✅ 胜率统计 (按位置/盲注)
✅ 手牌历史完整记录
✅ 牌型分布分析
✅ 下注习惯统计
✅ 导出CSV/JSON
✅ 可视化图表


---

## 🏆 锦标赛系统 / Tournament System / 錦標賽系統
🎖️ 每日挑战 (100盲注起步)
🏆 周赛积分榜
⚡ 限时赛 (15分钟)
💰 虚拟奖池系统
📜 比赛回放功能

## 🎨 主题系统 / Themes / 主題系統

🌙 夜间模式 (护眼)
☀️ 经典模式
🎰 拉斯维加斯
🧩 简约风
💎 豪华赌场
🎨 自定义配色


## 📊 详细统计 / Detailed Stats / 詳細統計
胜率 | 平均底池 | 总手数 | 最大连胜
VPIP/PFR | 3-bet频率 | Agg Factor
位置胜率 | 盲注胜率
牌型分布 | 下注热图



## 🛠️ 技术架构 / Tech Stack / 技術架構
🎮 渲染引擎: Electron / Pygame / Canvas
🎨 UI框架: React / Vue / Qt
📊 数据存储: SQLite / JSON
🎵 音效: Web Audio / Pygame mixer
📦 打包工具: Electron-builder / PyInstaller

## 📱 💰 联系 | Contact


📱 Telegram：@fox_lovemyself


📧 Email：lihongbo9414@gmail.com

## 产品截图
![13](https://github.com/user-attachments/assets/bc00bf28-558f-4742-8426-3e22fa25efeb)
![12](https://github.com/user-attachments/assets/1cc31f9c-705d-465d-888b-ce0f2c2f13d4)
![11](https://github.com/user-attachments/assets/76194b4d-51fa-433a-b290-52e3ec878da3)
![10](https://github.com/user-attachments/assets/6544287f-3bb0-4416-b821-0e34a6515120)
![08](https://github.com/user-attachments/assets/2e007e26-cd87-4f57-bcd4-3becc9cd7ee2)
![04](https://github.com/user-attachments/assets/0b0cebc6-4920-4263-9384-36db22c00dc3)
![01](https://github.com/user-attachments/assets/8235a957-7408-4b5f-a5dc-6c7cdb6c9380)
**[立即下载体验](https://github.com/deepseek7878/texas-holdem-desktop/releases/latest)**

## 🎮 完整游戏流程 / Game Flow / 遊戲流程
选择模式 → 设置盲注/人数

自动发底牌 (2张)

Pre-flop下注轮

Flop(3张公共牌) → 下注

Turn(4张) → 下注

River(5张) → 摊牌

自动牌型判断 → 结算

数据记录 → 下一手


## 🔌 开发者接口 / Developer API / 開發者介面

```javascript
// 创建游戏实例
const game = new TexasHoldem({players: 6, blinds: });[1][2]

// 模拟一手
game.dealHoleCards();
game.preflopBetting();
game.flop();
game.showdown();

// 获取结果
console.log(game.winner, game.pot);
```

## 📦 跨平台打包 / Cross-Platform Build / 跨平台打包

```bash
# 一键全平台打包
npm run build:all
# 输出: Windows.exe + macOS.dmg + Linux.AppImage

# 单平台
npm run build:win
npm run build:mac  
npm run build:linux
```

## 🎯 目标用户 / Target Users / 目標用戶
🎯 扑克发烧友 (离线练习)
📱 手机党 (桌面替代)
🎮 游戏开发者 (引擎参考)
📚 扑克教学 (演示工具)
💼 俱乐部运营 (数据分析)

text

## 🎵 沉浸式体验 / Immersive Experience / 沉浸式體驗
💰 筹码碰撞音效
🎴 平滑发牌动画
✨ 牌型高亮特效
🎉 胜利动画
🔊 环境音背景音乐
📱 响应式界面适配

## 📊 性能表现 / Performance / 效能表現

| 平台 | 内存占用 | 启动时间 | 帧率 |
|------|----------|----------|------|
| Windows | 85MB | 1.8s | 60fps |
| macOS | 92MB | 2.2s | 60fps |
| Linux | 78MB | 1.5s | 60fps |

## 🛠️ 版本发布 / Releases / 版本發佈

### 🚀 v1.0.0 (稳定版)
✅ 完整德州扑克规则  
✅ 多模式锦标赛  
✅ 详细数据统计  
✅ 6套主题皮肤  
✅ 全平台原生支持  




## ⭐ Key Features

- Offline playable poker game  
- AI opponents with different styles  
- Smooth desktop UI experience  
- Cross-platform support (Windows / macOS)
## 🧩 Architecture

- UI Layer (Desktop client)  
- Game Engine  
- State management  
- Event handling system  
## ❓ 常见问题 / FAQ / 常見問題

**Q: 支持联网对战吗？**  
**A:** 当前是联网版本开

**Q: 可以自定义规则吗？**  
**A:** 支持盲注/时间/人数自定义

**Q: 数据怎么导出？**  
**A:** CSV/JSON全量导出

**Q: 手机能玩吗？**  
**A:** 完美适配桌面，手机Web计划中

## 🤝 贡献指南 / Contributing / 貢獻指南





