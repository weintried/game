# a simple prototype, serves as a reference for the final game

import pygame
import random
import sys

pygame.init()

# 視窗大小
WIDTH, HEIGHT = 480, 640
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("飛行射擊範例")

clock = pygame.time.Clock()

# --- 遊戲物件設定 ---

# 玩家飛機
player_img = pygame.Surface((50, 50))
player_img.fill((0, 128, 255))  # 簡單用藍色方塊取代飛機圖片
player_rect = player_img.get_rect()
player_rect.center = (WIDTH // 2, HEIGHT - 60)  # 底部中央
player_speed = 5

# 子彈
bullet_img = pygame.Surface((5, 15))
bullet_img.fill((255, 255, 0))  # 黃色的子彈
bullets = []  # 儲存所有在場上的子彈 (rect)

# 敵機 (或隕石) 設定
enemy_img = pygame.Surface((40, 40))
enemy_img.fill((255, 0, 0))  # 紅色敵機
enemies = []  # 儲存所有在場上的敵機 (rect)
enemy_spawn_timer = 0
enemy_spawn_interval = 30  # 每隔幾幀就生成一台敵機
enemy_speed = 3

# 分數、遊戲狀態
score = 0
font = pygame.font.SysFont("Arial", 24)

running = True
while running:
    clock.tick(60)  # 維持 60 FPS

    # 1. 處理事件
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            # 左鍵點擊 => 發射子彈
            if event.button == 1:  # 1=左鍵, 2=中鍵, 3=右鍵
                bullet_rect = bullet_img.get_rect()
                bullet_rect.center = (player_rect.centerx, player_rect.top)
                bullets.append(bullet_rect)

    # 2. 取得鍵盤狀態 (移動玩家)
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT] and player_rect.left > 0:
        player_rect.x -= player_speed
    if keys[pygame.K_RIGHT] and player_rect.right < WIDTH:
        player_rect.x += player_speed
    if keys[pygame.K_UP] and player_rect.top > 0:
        player_rect.y -= player_speed
    if keys[pygame.K_DOWN] and player_rect.bottom < HEIGHT:
        player_rect.y += player_speed

    # 3. 更新子彈位置
    for b in bullets[:]:
        b.y -= 10  # 子彈往上飛
        if b.bottom < 0:
            bullets.remove(b)  # 超出畫面上緣就刪除

    # 4. 隨機生成敵機
    enemy_spawn_timer += 1
    if enemy_spawn_timer >= enemy_spawn_interval:
        enemy_spawn_timer = 0
        enemy_rect = enemy_img.get_rect()
        enemy_rect.x = random.randint(0, WIDTH - enemy_rect.width)
        enemy_rect.y = -enemy_rect.height  # 從畫面頂端上方出現
        enemies.append(enemy_rect)

    # 5. 更新敵機位置
    for e in enemies[:]:
        e.y += enemy_speed
        if e.top > HEIGHT:
            enemies.remove(e)  # 敵機超出畫面下方就刪除

    # 6. 碰撞偵測 (子彈 vs 敵機)
    for b in bullets[:]:
        for e in enemies[:]:
            if b.colliderect(e):
                # 子彈與敵機碰撞
                bullets.remove(b)
                enemies.remove(e)
                score += 10
                break  # 該子彈已經銷毀，不再檢查後續敵機

    # 7. 玩家與敵機碰撞（若需要顯示Game Over，可自行加）
    for e in enemies:
        if e.colliderect(player_rect):
            running = False

    # 8. 繪製畫面
    screen.fill((0, 0, 0))  # 黑色背景

    # 繪製玩家
    screen.blit(player_img, player_rect)

    # 繪製子彈
    for b in bullets:
        screen.blit(bullet_img, b)

    # 繪製敵機
    for e in enemies:
        screen.blit(enemy_img, e)

    # 繪製分數
    score_surface = font.render(f"Score: {score}", True, (255, 255, 255))
    screen.blit(score_surface, (10, 10))

    # 更新畫面
    pygame.display.flip()

pygame.quit()
sys.exit()