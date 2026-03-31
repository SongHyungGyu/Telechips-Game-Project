<!DOCTYPE html>
<html lang="ko">
<head>
  <meta charset="UTF-8" />
  <title>두근두근 두더지의 프러포즈 작전 - API 문서</title>
  <style>
    :root {
      --bg: #f3f4ff;
      --bg-alt: #eef2ff;
      --panel: #ffffff;
      --accent: #6366f1;
      --accent-soft: rgba(99,102,241,0.12);
      --accent-strong: rgba(79,70,229,0.16);
      --accent-stronger: rgba(79,70,229,0.3);
      --border-subtle: rgba(148,163,184,0.7);
      --text-main: #111827;
      --text-muted: #4b5563;
      --text-soft: #6b7280;
      --chip-bg: #eef2ff;
      --shadow-soft: 0 18px 45px rgba(148,163,184,0.45);
      --radius-lg: 18px;
      --radius-pill: 999px;
    }

    * {
      box-sizing: border-box;
    }

    body {
      margin: 0;
      padding: 0;
      font-family: system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif;
      background: radial-gradient(circle at top, #e0f2fe 0, #eef2ff 40%, #f9fafb 100%);
      color: var(--text-main);
      line-height: 1.6;
    }

    header {
      position: sticky;
      top: 0;
      z-index: 20;
      backdrop-filter: blur(16px);
      background: linear-gradient(135deg, rgba(255,255,255,0.94), rgba(239,246,255,0.96));
      border-bottom: 1px solid rgba(191,219,254,0.9);
      box-shadow: 0 10px 28px rgba(148,163,184,0.5);
    }

    .header-inner {
      max-width: 1240px;
      margin: 0 auto;
      padding: 18px 28px;
      display: flex;
      align-items: center;
      justify-content: space-between;
      gap: 18px;
      flex-wrap: wrap;
    }

    .title-block h1 {
      margin: 0 0 4px 0;
      font-size: 26px;
      letter-spacing: 0.02em;
      color: #111827;
    }

    .title-block p {
      margin: 0;
      font-size: 13px;
      color: var(--text-soft);
    }

    .tagline {
      display: inline-flex;
      align-items: center;
      gap: 8px;
      padding: 4px 12px;
      border-radius: var(--radius-pill);
      border: 1px solid rgba(191,219,254,0.9);
      font-size: 11px;
      color: var(--text-soft);
      background: radial-gradient(circle at top left, rgba(219,234,254,0.9), rgba(239,246,255,0.9));
    }

    .tag-dot {
      width: 7px;
      height: 7px;
      border-radius: 999px;
      background: #22c55e;
      box-shadow: 0 0 0 4px rgba(34,197,94,0.2);
    }

    main {
      max-width: 1240px;
      margin: 26px auto 60px;
      padding: 0 28px 32px;
      display: grid;
      grid-template-columns: minmax(0, 260px) minmax(0, 1fr);
      gap: 20px;
      align-items: flex-start;
    }

    @media (max-width: 960px) {
      main {
        grid-template-columns: minmax(0, 1fr);
      }
    }

    .side-panel {
      background: radial-gradient(circle at top left, rgba(219,234,254,0.9), rgba(255,255,255,0.98));
      border-radius: 22px;
      padding: 18px 18px 20px;
      border: 1px solid rgba(191,219,254,0.95);
      box-shadow: 0 14px 36px rgba(148,163,184,0.6);
      position: sticky;
      top: 82px;
    }

    .side-title {
      font-size: 13px;
      text-transform: uppercase;
      letter-spacing: 0.15em;
      color: #6b7280;
      margin-bottom: 10px;
    }

    .side-desc {
      font-size: 13px;
      color: #111827;
      margin-bottom: 12px;
    }

    .chip-row {
      display: flex;
      flex-wrap: wrap;
      gap: 6px;
      margin-bottom: 14px;
    }

    .chip {
      font-size: 11px;
      padding: 3px 10px;
      border-radius: 999px;
      background: #e5edff;
      border: 1px solid rgba(191,219,254,0.95);
      color: #1f2937;
    }

    .module-buttons {
      display: flex;
      flex-wrap: wrap;
      gap: 6px;
      margin-top: 8px;
    }

    .module-btn {
      border: 1px solid rgba(209,213,219,0.9);
      background: radial-gradient(circle at top left, #ffffff, #f3f4ff);
      color: var(--text-muted);
      border-radius: var(--radius-pill);
      padding: 5px 11px;
      font-size: 12px;
      cursor: pointer;
      display: inline-flex;
      align-items: center;
      gap: 6px;
      transition: all 0.16s ease-out;
    }

    .module-btn span.dot {
      width: 7px;
      height: 7px;
      border-radius: 999px;
      background: rgba(156,163,175,0.8);
    }

    .module-btn.active {
      background: radial-gradient(circle at top left, #e0f2fe, #bfdbfe);
      border-color: rgba(129,140,248,0.9);
      color: #111827;
      box-shadow: 0 12px 32px rgba(129,140,248,0.55);
    }

    .module-btn.active span.dot {
      background: #1d4ed8;
    }

    .module-btn:hover:not(.active) {
      border-color: rgba(129,140,248,0.9);
      color: #111827;
      transform: translateY(-1px);
      box-shadow: 0 8px 22px rgba(148,163,184,0.6);
    }

    .hint {
      margin-top: 12px;
      font-size: 11px;
      color: var(--text-soft);
    }

    .content {
      border-radius: 26px;
      padding: 20px 22px 26px;
      background: radial-gradient(circle at top left, #eff6ff, #ffffff);
      border: 1px solid rgba(199,210,254,0.95);
      box-shadow: var(--shadow-soft);
      position: relative;
      overflow: hidden;
    }

    .content::before {
      content: "";
      position: absolute;
      inset: -60%;
      background:
        radial-gradient(circle at 0% 0%, rgba(125,211,252,0.3), transparent 55%),
        radial-gradient(circle at 100% 0%, rgba(244,114,182,0.2), transparent 60%);
      opacity: 0.7;
      pointer-events: none;
    }

    .content-inner {
      position: relative;
      z-index: 1;
    }

    h2 {
      margin-top: 0;
      margin-bottom: 10px;
      font-size: 19px;
      display: flex;
      align-items: center;
      gap: 8px;
      color: #111827;
    }

    h2 .section-tag {
      font-size: 11px;
      text-transform: uppercase;
      letter-spacing: 0.12em;
      color: #4338ca;
      padding: 2px 9px;
      border-radius: 999px;
      border: 1px solid rgba(165,180,252,0.9);
      background: rgba(224,231,255,0.9);
    }

    h3 {
      margin-top: 26px;
      margin-bottom: 8px;
      font-size: 16px;
      color: #111827;
    }

    p {
      font-size: 13px;
      color: #1f2937;
    }

    .section-intro {
      font-size: 13px;
      color: #1f2937;
      margin-bottom: 12px;
    }

    .api-card {
      background: #ffffff;
      border-radius: 16px;
      padding: 14px 14px 14px;
      margin-top: 10px;
      border: 1px solid rgba(209,213,219,0.9);
      box-shadow: 0 8px 24px rgba(148,163,184,0.45);
    }

    .api-header {
      display: flex;
      align-items: baseline;
      justify-content: space-between;
      gap: 8px;
      flex-wrap: wrap;
      margin-bottom: 4px;
    }

    .api-name {
      font-family: "JetBrains Mono", ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", "Courier New", monospace;
      font-size: 13px;
      color: #111827;
    }

    .api-kind {
      font-size: 11px;
      padding: 2px 8px;
      border-radius: 999px;
      border: 1px solid rgba(209,213,219,0.9);
      background: #f3f4ff;
      color: #4b5563;
    }

    .api-signature {
      margin-top: 6px;
      padding: 7px 9px;
      border-radius: 10px;
      background: #f9fafb;
      border: 1px solid rgba(209,213,219,0.9);
      font-family: "JetBrains Mono", ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", "Courier New", monospace;
      font-size: 12px;
      white-space: pre;
      overflow-x: auto;
      color: #111827;
    }

    .api-meta {
      margin-top: 4px;
      font-size: 11px;
      color: #6b7280;
    }

    ul {
      padding-left: 18px;
      margin: 6px 0 2px;
    }

    ul li {
      font-size: 13px;
      color: #111827;
      margin-bottom: 1px;
    }

    .badge {
      display: inline-flex;
      align-items: center;
      justify-content: center;
      font-size: 11px;
      padding: 2px 8px;
      border-radius: 999px;
      background: #eef2ff;
      border: 1px solid rgba(191,219,254,0.9);
      color: #1f2937;
      margin-right: 4px;
      margin-bottom: 2px;
    }

    code {
      font-family: "JetBrains Mono", ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", "Courier New", monospace;
      font-size: 12px;
      background: #f3f4ff;
      border-radius: 4px;
      padding: 1px 4px;
      border: 1px solid rgba(209,213,219,0.9);
      color: #111827;
    }

    .module-section {
      display: none;
      animation: fadeIn 0.18s ease-out;
    }

    .module-section.active {
      display: block;
    }

    .pill-row {
      margin-top: 4px;
      margin-bottom: 10px;
    }

    .pill {
      display: inline-flex;
      align-items: center;
      gap: 6px;
      font-size: 11px;
      color: #111827;
      padding: 3px 9px;
      border-radius: 999px;
      border: 1px solid rgba(209,213,219,0.9);
      background: #f3f4ff;
      margin-right: 4px;
      margin-bottom: 4px;
    }

    .pill span {
      font-size: 10px;
      text-transform: uppercase;
      letter-spacing: 0.14em;
      color: #4f46e5;
    }

    footer {
      max-width: 1240px;
      margin: 0 auto 22px;
      padding: 0 28px;
      font-size: 11px;
      color: var(--text-soft);
      display: flex;
      justify-content: space-between;
      gap: 8px;
      flex-wrap: wrap;
    }

    @keyframes fadeIn {
      from {
        opacity: 0;
        transform: translateY(4px);
      }
      to {
        opacity: 1;
        transform: translateY(0);
      }
    }

    hr {
      border: none;
      border-top: 1px dashed rgba(209,213,219,0.9);
      margin: 12px 0;
    }
  </style>
</head>
<body>
<header>
  <div class="header-inner">
    <div class="title-block">
      <h1>두근두근 두더지의 프러포즈 작전</h1>
      <p>Allegro 기반 2D 타일식 스테이지 게임 &mdash; 모듈별 C API 정리</p>
    </div>
    <div class="tagline">
      <span class="tag-dot"></span>
      <span>실제 코드 기반 자동 정리 · 밝은 테마의 HTML 문서</span>
    </div>
  </div>
</header>

<main>
  <aside class="side-panel">
    <div class="side-title">Module Navigator</div>
    <div class="side-desc">
      아래 버튼을 눌러서 <strong>모듈별 API 설명</strong>을 전환할 수 있습니다.
    </div>
    <div class="chip-row">
      <span class="chip">Allegro 5</span>
      <span class="chip">C 언어</span>
      <span class="chip">2D 타일 · 스테이지</span>
    </div>

    <div class="module-buttons">
      <button class="module-btn active" data-target="mod-overview">
        <span class="dot"></span>개요 / 실행 흐름
      </button>
      <button class="module-btn" data-target="mod-core">
        <span class="dot"></span>코어 시스템 (LIB_DDG)
      </button>
      <button class="module-btn" data-target="mod-stage">
        <span class="dot"></span>스테이지·맵 (LIB_stage + stage1~3)
      </button>
      <button class="module-btn" data-target="mod-ddg">
        <span class="dot"></span>플레이어·추격자 (for_ddg)
      </button>
      <button class="module-btn" data-target="mod-worm">
        <span class="dot"></span>지렁이 / 탄막 (for_worm · LIB_c_worm · LIB_shot)
      </button>
      <button class="module-btn" data-target="mod-flower">
        <span class="dot"></span>꽃 아이템 (for_flower)
      </button>
      <button class="module-btn" data-target="mod-user">
        <span class="dot"></span>유저·랭킹 (for_user)
      </button>
      <button class="module-btn" data-target="mod-firstpage">
        <span class="dot"></span>첫 화면 / 설명 (LIB_first_page)
      </button>
    </div>

    <div class="hint">
      · 모듈 버튼을 클릭하면 오른쪽에 해당 모듈 API와 사용 흐름이 보입니다.<br/>
      · 함수명 / 구조체명은 실제 코드와 동일하게 사용했습니다.
    </div>
  </aside>

  <section class="content">
    <div class="content-inner">

      <!-- 1. 개요 / 실행 흐름 -->
      <section id="mod-overview" class="module-section active">
        <h2>
          프로젝트 개요 · 실행 흐름
          <span class="section-tag">Overview</span>
        </h2>
        <p class="section-intro">
          <code>DDG_Girlfriend</code>는 Allegro 라이브러리를 사용한 2D 타일식 미니 게임입니다.
          플레이어 캐릭터 DDG를 조작해 여러 스테이지를 클리어하고, 지렁이/탄막/추격자를 피하면서 목표 지점과 꽃을 모으는 방식으로 진행됩니다.
        </p>

        <div class="pill-row">
          <span class="pill"><span>Entry</span> MAIN_DDG.c</span>
          <span class="pill"><span>Core</span> LIB_DDG.c / LIB_DDG.h</span>
          <span class="pill"><span>Stage</span> LIB_stage.h, stage1/2/3.c</span>
        </div>

        <div class="api-card">
          <div class="api-header">
            <div class="api-name">int main(void)</div>
            <div class="api-kind">엔트리 포인트</div>
          </div>
          <div class="api-signature">
#include "LIB_DDG.h"
#include "LIB_stage.h"
#include "LIB_first_page.h"
#include "for_ddg.h"
#include "for_user.h"

int main(void);
          </div>
          <p class="section-intro">
            게임의 시작 지점으로, Allegro 및 게임 시스템 초기화 → 유저/플레이어/스테이지 초기화 → 메인 이벤트 루프를 구성합니다.
          </p>
          <ul>
            <li><strong>초기화 흐름</strong>
              <ul>
                <li><code>init_system()</code> : Allegro, 오디오, 폰트 등 전역 시스템 초기화</li>
                <li><code>SYSTEM* sys = init_game_system()</code> : 디스플레이, 이벤트 큐, 타이머, 기본 폰트 세팅</li>
                <li><code>User* user = init_User()</code> : 유저 정보 구조체 생성</li>
                <li><code>DDG* ddg = init_ddg()</code> : 플레이어 캐릭터 생성</li>
                <li><code>Stage* stage1/2/3 = init_stageX()</code> : 각 스테이지별 데이터/맵 초기화</li>
              </ul>
            </li>
            <li><strong>메인 루프</strong>
              <ul>
                <li><code>al_wait_for_event(sys-&gt;queue, &amp;ev)</code>로 이벤트 대기</li>
                <li><code>keyboard_update(&amp;ev)</code>로 키 입력 상태 갱신</li>
                <li>ESC 입력 시 현재 모드에 따라 <code>after_stage(stageX, MODE_FIRST_PAGE)</code> 호출</li>
                <li>전역 <code>mode</code> 값에 따라
                  <ul>
                    <li><code>MODE_FIRST_PAGE</code> → <code>run_first_page</code></li>
                    <li><code>MODE_STAGE1/2/3</code> → 각각 <code>run_stage1/2/3</code></li>
                    <li><code>MODE_SET_STAGEX</code> → <code>set_stageX</code>로 스테이지 진입 준비</li>
                    <li><code>MODE_EXPLAIN</code> → <code>run_explanation_page</code></li>
                  </ul>
                </li>
              </ul>
            </li>
          </ul>
        </div>

        <h3>전역 상태 및 게임 모드</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">GameMode, mode, play_time</div>
            <div class="api-kind">게임 상태 관리</div>
          </div>
          <div class="api-signature">
typedef enum {
    MODE_FIRST_PAGE = 0,
    MODE_STAGE1,
    MODE_STAGE2,
    MODE_STAGE3,
    MODE_SET_STAGE1,
    MODE_SET_STAGE2,
    MODE_SET_STAGE3,
    MODE_EXPLAIN,
    MODE_COUNT
} GameMode;

int mode;        // 현재 게임 모드
int play_time;   // 전체 플레이 시간(프레임 단위, 60프레임 = 약 1초)
          </div>
          <ul>
            <li><strong>mode</strong>: 현재 게임이 어느 화면/스테이지에 있는지 나타내며 메인 루프의 분기 기준입니다.</li>
            <li><strong>play_time</strong>: 프레임 단위 누적 시간으로, 각 스테이지 루프에서 <code>ev.type == ALLEGRO_EVENT_TIMER</code>일 때 증가시킵니다.</li>
            <li>스테이지 클리어 시 <code>play_time / 60</code>을 사용해 분 단위(또는 초 단위)에 가까운 기록을 랭킹에 저장합니다.</li>
          </ul>
        </div>
      </section>

      <!-- 2. 코어 시스템 -->
      <section id="mod-core" class="module-section">
        <h2>
          코어 시스템 · Allegro 래퍼
          <span class="section-tag">LIB_DDG</span>
        </h2>
        <p class="section-intro">
          게임 전역에서 사용하는 Allegro 초기화, 디스플레이/이벤트 시스템 생성, 리소스 로딩, 키보드 입력 관리 등을 담당하는 코어 모듈입니다.
          다른 모듈들은 이 API를 통해 공통 리소스를 사용합니다.
        </p>

        <h3>시스템 초기화</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">void must_init(bool test, const char* description)</div>
            <div class="api-kind">유틸 함수</div>
          </div>
          <div class="api-signature">
void must_init(bool test, const char* description);
          </div>
          <ul>
            <li><strong>설명</strong>: Allegro 함수 호출 결과를 검사하여 실패 시 메시지를 출력하고 프로그램을 종료합니다.</li>
            <li><strong>사용 위치</strong>: Allegro 초기화, 디스플레이 생성, 타이머, 폰트, 오디오 로딩 등 필수 자원 로딩 직후.</li>
          </ul>
        </div>

        <div class="api-card">
          <div class="api-header">
            <div class="api-name">void init_system(void)</div>
            <div class="api-kind">전역 라이브러리 초기화</div>
          </div>
          <div class="api-signature">
void init_system(void);
          </div>
          <ul>
            <li><strong>설명</strong>: 게임 실행 전에 한 번만 호출되며 Allegro와 관련 애드온을 초기화합니다.</li>
            <li><strong>내부 동작</strong>
              <ul>
                <li><code>al_init()</code>, <code>al_install_keyboard()</code></li>
                <li><code>al_init_image_addon()</code>, <code>al_init_font_addon()</code>, <code>al_init_ttf_addon()</code></li>
                <li><code>al_install_audio()</code>, <code>al_init_acodec_addon()</code>, <code>al_reserve_samples(16)</code></li>
              </ul>
            </li>
          </ul>
        </div>

        <h3>디스플레이 / 이벤트 시스템</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">ALLEGRO_DISPLAY* create_display(void)</div>
            <div class="api-kind">디스플레이 생성</div>
          </div>
          <div class="api-signature">
ALLEGRO_DISPLAY* create_display(void);
          </div>
          <ul>
            <li><strong>설명</strong>: 해상도 <code>DISP_W = 1200</code>, <code>DISP_H = 900</code> 크기의 메인 디스플레이를 생성합니다.</li>
          </ul>
        </div>

        <div class="api-card">
          <div class="api-header">
            <div class="api-name">typedef struct SYSTEM { ... } SYSTEM;</div>
            <div class="api-kind">게임 시스템 컨텍스트</div>
          </div>
          <div class="api-signature">
typedef struct SYSTEM {
    ALLEGRO_DISPLAY*      display;
    ALLEGRO_EVENT_QUEUE*  queue;
    ALLEGRO_TIMER*        timer;
    ALLEGRO_FONT*         font;
} SYSTEM;

SYSTEM* init_game_system(void);
          </div>
          <ul>
            <li><strong>설명</strong>: 디스플레이, 이벤트 큐, 타이머, 기본 폰트를 하나의 구조체로 묶어 관리합니다.</li>
            <li><strong><code>init_game_system</code> 동작</strong>
              <ul>
                <li><code>create_display()</code>로 디스플레이 생성</li>
                <li><code>al_create_event_queue()</code>로 큐 생성</li>
                <li><code>al_load_ttf_font("resource/font/Inkfree.ttf", 30, 0)</code>로 기본 폰트 로드</li>
                <li>60 FPS 타이머 생성 후 이벤트 소스(키보드/디스플레이/타이머)를 모두 큐에 등록</li>
              </ul>
            </li>
          </ul>
        </div>

        <h3>리소스 로딩 / 오디오 스트림</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">ALLEGRO_BITMAP* load_image(const char* path)</div>
            <div class="api-kind">이미지 로딩</div>
          </div>
          <div class="api-signature">
ALLEGRO_BITMAP* load_image(const char* path);
ALLEGRO_SAMPLE* load_aud(const char* path);
ALLEGRO_AUDIO_STREAM* load_stream(const char* path);
void play_stream(ALLEGRO_AUDIO_STREAM* stream);
void detach_stream(ALLEGRO_AUDIO_STREAM* stream);
void destroy_stream(ALLEGRO_AUDIO_STREAM* stream);
          </div>
          <ul>
            <li><strong>설명</strong>: 이미지(<code>al_load_bitmap</code>), 단발성 샘플(<code>al_load_sample</code>), 스트리밍 BGM(<code>al_load_audio_stream</code>)을 로딩하는 헬퍼 함수입니다.</li>
            <li><strong>경로</strong>
              <ul>
                <li>이미지: <code>PATH = "resource/img/"</code></li>
                <li>오디오: <code>AUDIOPATH = "resource/aud/"</code></li>
              </ul>
            </li>
            <li><strong>BGM 재생</strong>
              <ul>
                <li><code>play_stream</code>: 루프 모드로 설정 후 기본 믹서에 붙여 재생</li>
                <li><code>detach_stream</code>, <code>destroy_stream</code>로 필요 시 분리/해제</li>
              </ul>
            </li>
          </ul>
        </div>

        <h3>키보드 입력 관리</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">unsigned char key[ALLEGRO_KEY_MAX]</div>
            <div class="api-kind">입력 상태 배열</div>
          </div>
          <div class="api-signature">
#define KEY_SEEN 1
#define KEY_DOWN 2

void keyboard_init(void);
void keyboard_update(ALLEGRO_EVENT* event);
          </div>
          <ul>
            <li><strong>설명</strong>: 프레임 단위로 키가 눌린/유지되고 있는 상태를 추적하기 위한 간단한 키 입력 시스템입니다.</li>
            <li><strong>사용 패턴</strong>
              <ul>
                <li>타이머 이벤트 시 전체 키에 대해 <code>KEY_SEEN</code> 플래그 초기화</li>
                <li>KEY_DOWN 이벤트 시 해당 키에 <code>KEY_SEEN | KEY_DOWN</code> 설정</li>
                <li>KEY_UP 이벤트 시 <code>KEY_DOWN</code> 플래그 제거</li>
                <li>다른 모듈에서는 <code>key[ALLEGRO_KEY_LEFT]</code> 등으로 상태를 읽습니다.</li>
              </ul>
            </li>
          </ul>
        </div>
      </section>

      <!-- 3. 스테이지 · 맵 -->
      <section id="mod-stage" class="module-section">
        <h2>
          스테이지 · 맵 시스템
          <span class="section-tag">LIB_stage + stage1/2/3</span>
        </h2>
        <p class="section-intro">
          스테이지별 맵, 타일, 지형(벽/길/늪), 웜/플라워/추격자/탄막 등의 구성을 관리하는 모듈입니다.
          <code>Stage</code> 구조체 하나가 스테이지에 필요한 대부분의 상태를 갖고 있습니다.
        </p>

        <h3>기본 상수 / 타일 / 스테이지 구조체</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">타일 / 맵 / 스테이지 정의</div>
            <div class="api-kind">자료 구조</div>
          </div>
          <div class="api-signature">
#define ddg_size   50
#define TILE_SIZE  60
#define tile_w_num 20
#define tile_h_num 15

typedef enum {
    WALL  = 1,
    ROAD  = 0,
    MARSH = 2
} TileType;

typedef struct {
    int x, y, w, h;
    int type; // 0: 벽, 1: 길, 2: 늪 (주석 기준)
} tile;

typedef struct {
    tile tiles[tile_h_num][tile_w_num];
} Map;

typedef struct {
    int stage;
    Map map;
    ALLEGRO_BITMAP* mapCache;
    ALLEGRO_BITMAP* roadTile;
    ALLEGRO_BITMAP* wallTile;
    ALLEGRO_BITMAP* marshTile;
    ALLEGRO_AUDIO_STREAM* bgm;
    void (*initMap)(Map* m);
    int sx, sy;         // 시작 위치
    C_WORM** c_worms;
    int c_worm_count;
    int wormNum;
    worm** worms;
    flower** flowers;
    int flower_cnt;
    Chaser* chaser;
    ALLEGRO_BITMAP* ddg_girl;
} Stage;
          </div>
          <ul>
            <li><strong>타일 좌표계</strong>: <code>TILE_SIZE</code> 단위의 격자를 사용하여 맵 전체를 구성합니다.</li>
            <li><strong>Map</strong>: 20x15(가로x세로) 타일 배열로 한 화면을 구성합니다.</li>
            <li><strong>Stage</strong>:
              <ul>
                <li><code>map</code>과 <code>mapCache</code> (타일을 미리 렌더링해 둔 비트맵)를 함께 소유</li>
                <li>여러 종류의 적/오브젝트 포인터 배열(<code>worms</code>, <code>c_worms</code>, <code>flowers</code>, <code>chaser</code>)을 포함</li>
                <li><code>initMap</code> 함수 포인터로 각 스테이지가 타일 배치를 다르게 설정</li>
              </ul>
            </li>
          </ul>
        </div>

        <h3>공용 스테이지 API</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">Stage* init_stage1/2/3(void)</div>
            <div class="api-kind">스테이지 생성</div>
          </div>
          <div class="api-signature">
Stage* init_stage1(void);
Stage* init_stage2(void);
Stage* init_stage3(void);

void init_stage(Stage* s);
void after_stage(Stage* s, GameMode toGo);
void renderMap(Stage* s);
          </div>
          <ul>
            <li><strong>설명</strong>: 각 스테이지 별로 타일 배치, 웜/꽃/탄막 웜, 추격자, 배경음악 등을 세팅합니다.</li>
            <li><strong><code>init_stageX</code> 역할</strong>
              <ul>
                <li><code>initMap</code> 포인터를 해당 스테이지 전용 <code>initStageXMap</code>로 설정</li>
                <li>지렁이/꽃/추격자(<code>init_chaser</code>), BGM(<code>load_stream</code>), <code>ddg_girl</code> 이미지 로딩</li>
                <li>공용 함수 <code>init_stage</code>로 타일 비트맵 및 캐시 생성</li>
              </ul>
            </li>
            <li><strong><code>after_stage</code></strong>: 클리어 또는 ESC 등으로 스테이지를 빠져나갈 때 BGM 처리, 모드 전환 등을 수행합니다.</li>
          </ul>
        </div>

        <h3>stage1.c &mdash; 기본 스테이지</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">Stage* init_stage1(void)</div>
            <div class="api-kind">Stage1 설정</div>
          </div>
          <div class="api-signature">
static void initStage1Map(Map* m);  // 내부 전용

Stage* init_stage1(void);
void   run_stage1(User* user, DDG* ddg, Stage* s, SYSTEM* sys, ALLEGRO_EVENT ev);
          </div>
          <ul>
            <li><strong>맵 특징</strong>: 바깥 테두리는 모두 벽(<code>WALL</code>), 내부는 전부 길(<code>ROAD</code>)인 비교적 단순한 맵입니다.</li>
            <li><strong>적 구성</strong>
              <ul>
                <li>수평 이동 지렁이 4마리 (<code>worms</code>)</li>
                <li>플레이어를 따라오는 <code>Chaser</code> 1마리</li>
              </ul>
            </li>
            <li><strong>클리어 조건</strong>: 도착 지점(<code>ax1, ay1</code>) 근처에 플레이어가 진입하면 Stage2 세팅 모드(<code>MODE_SET_STAGE2</code>)로 전환.</li>
            <li><strong>루프 동작 (<code>run_stage1</code>)</strong>
              <ul>
                <li>타이머 이벤트마다 <code>update_stage1_by_time</code> 호출 → 웜/추격자/플레이어 이동 및 충돌 처리</li>
                <li><code>render_stage1</code>에서 맵, DDG, 웜, 추격자, HUD, 플레이 타임 렌더링</li>
              </ul>
            </li>
          </ul>
        </div>

        <h3>stage2.c &mdash; 늪 + 꽃 수집</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">Stage* init_stage2(void)</div>
            <div class="api-kind">Stage2 설정</div>
          </div>
          <div class="api-signature">
static void initStage2Map(Map* m);

Stage* init_stage2(void);
void   run_stage2(User* user, DDG* ddg, Stage* s, SYSTEM* sys, ALLEGRO_EVENT ev);
          </div>
          <ul>
            <li><strong>맵 특징</strong>
              <ul>
                <li>테두리는 벽, 내부 일부 열(j=5,6,13,14)을 <code>MARSH</code>(늪) 지형으로 설정</li>
                <li>늪 지형 위에서는 <code>update_ddg</code>에서 이동 속도가 절반으로 감소</li>
              </ul>
            </li>
            <li><strong>오브젝트</strong>
              <ul>
                <li>수평 웜 4마리 (Stage1과 유사)</li>
                <li>꽃(<code>flower</code>) 12개: 여러 타일 위치에 배치, <code>s-&gt;flower_cnt</code>로 남은 개수 관리</li>
              </ul>
            </li>
            <li><strong>클리어 조건</strong>
              <ul>
                <li>플레이어가 도착 지점(<code>ax2, ay2</code>)에 도달</li>
                <li><code>s-&gt;flower_cnt == 0</code> (모든 꽃 수집)</li>
              </ul>
            </li>
          </ul>
        </div>

        <h3>stage3.c &mdash; 탄막 웜 + 복합 지형</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">Stage* init_stage3(void)</div>
            <div class="api-kind">Stage3 설정</div>
          </div>
          <div class="api-signature">
static int stage3_blueprint[tile_h_num][tile_w_num];
static void initStage3Map(Map* m);

Stage* init_stage3(void);
void   run_stage3(User* user, DDG* ddg, Stage* s, SYSTEM* sys, ALLEGRO_EVENT ev);
          </div>
          <ul>
            <li><strong>맵 특징</strong>: 2차원 배열 <code>stage3_blueprint</code>를 이용해 복잡한 길/벽 패턴을 구성합니다.</li>
            <li><strong>적/오브젝트 구성</strong>
              <ul>
                <li>수평/수직 이동 웜 여러 마리 (10마리)</li>
                <li>탄막 지렁이(<code>C_WORM</code>) 3마리: 주기적으로 탄을 발사</li>
                <li>꽃 4개 &amp; <code>flower_cnt</code> 관리</li>
              </ul>
            </li>
            <li><strong>피격 처리</strong>
              <ul>
                <li><code>col_worms</code> 또는 <code>col_c_worm_shots</code>가 true면 플레이어 피격 처리</li>
              </ul>
            </li>
            <li><strong>최종 클리어 조건</strong>
              <ul>
                <li>도착 지점 + 모든 꽃 수집 후 → <code>set_User(..., 3, play_time / 60)</code></li>
                <li><code>save_User(user)</code>로 기록 저장, <code>after_stage</code> 후 첫 페이지로 복귀, <code>render_ending()</code> 호출</li>
              </ul>
            </li>
          </ul>
        </div>
      </section>

      <!-- 4. 플레이어 / 추격자 -->
      <section id="mod-ddg" class="module-section">
        <h2>
          플레이어 DDG · 추격자
          <span class="section-tag">for_ddg.c / for_ddg.h</span>
        </h2>
        <p class="section-intro">
          DDG 캐릭터의 이동/애니메이션, 체력 HUD, 피격 처리와 DDG를 쫓아오는 <code>Chaser</code> 적의 AI를 담당하는 모듈입니다.
        </p>

        <h3>초기화</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">DDG* init_ddg(void)</div>
            <div class="api-kind">플레이어 생성</div>
          </div>
          <div class="api-signature">
DDG*   init_ddg(void);
Chaser* init_chaser(int start_x, int start_y);
          </div>
          <ul>
            <li><strong><code>init_ddg</code></strong>
              <ul>
                <li>이미지: <code>ddg.png</code>, 하트: <code>heart.png</code></li>
                <li>사운드: <code>wormSound.wav</code>, <code>flowerSound.wav</code></li>
                <li>초기 위치: <code>x = TILE_SIZE * 1</code>, <code>y = TILE_SIZE * 1</code></li>
                <li>life=3, speed=5, 애니메이션 인덱스(<code>w</code>)를 0으로 시작</li>
              </ul>
            </li>
            <li><strong><code>init_chaser</code></strong>
              <ul>
                <li>시작 위치: 인자로 지정</li>
                <li>speed=2 (플레이어보다 조금 느림)</li>
                <li>이미지: <code>fox.png</code></li>
              </ul>
            </li>
          </ul>
        </div>

        <h3>이동 및 충돌</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">void update_ddg(DDG* ddg, Stage* s)</div>
            <div class="api-kind">플레이어 이동</div>
          </div>
          <div class="api-signature">
bool col_wall(int nx, int ny, Map* m);
bool col_marsh(int nx, int ny, Map* m);

void update_ddg(DDG* ddg, Stage* s);
          </div>
          <ul>
            <li><strong>col_wall / col_marsh</strong>
              <ul>
                <li><code>(nx, ny)</code> 좌표가 어느 타일에 속하는지 계산 후, 그 타일의 타입이 벽(<code>WALL</code>)인지, 늪(<code>MARSH</code>)인지 판정.</li>
              </ul>
            </li>
            <li><strong><code>update_ddg</code> 동작</strong>
              <ul>
                <li>전역 <code>key[]</code> 상태를 읽어 좌/우/상/하 이동 방향 결정</li>
                <li>다음 위치에서 벽이 아니면 이동, 늪이면 이동 속도를 절반으로 감소</li>
                <li>방향에 따라 스프라이트 시트의 <code>w</code> 값(0/100/200/300)으로 방향 프레임 선택</li>
              </ul>
            </li>
          </ul>
        </div>

        <div class="api-card">
          <div class="api-header">
            <div class="api-name">void update_chaser(Chaser* chaser, DDG* ddg, Map* m)</div>
            <div class="api-kind">추격 AI</div>
          </div>
          <div class="api-signature">
void update_chaser(Chaser* chaser, DDG* ddg, Map* m);
bool check_collision_with_chaser(DDG* ddg, Chaser* chaser);
          </div>
          <ul>
            <li><strong>이동 로직</strong>
              <ul>
                <li>DDG의 x/y 좌표와 비교하여, 각 축별(먼저 X, 나중에 Y)로 플레이어 방향으로 한 스텝씩 이동</li>
                <li>이동 전 <code>col_wall</code>을 사용해 벽 충돌 검사 후 이동</li>
              </ul>
            </li>
            <li><strong>충돌 판정</strong>
              <ul>
                <li><code>check_collision_with_chaser</code>는 <code>ddg_size/2</code> 범위 내에 있을 경우 충돌로 간주</li>
                <li>충돌 시 각 스테이지의 <code>update_ddg_after_attack</code>을 호출해 피격 처리</li>
              </ul>
            </li>
          </ul>
        </div>

        <h3>렌더링 / 피격 처리</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">void render_ddg(DDG* ddg)</div>
            <div class="api-kind">플레이어 렌더</div>
          </div>
          <div class="api-signature">
void render_ddg(DDG* ddg);
void render_hud(DDG* ddg);
void render_chaser(Chaser* chaser);
void update_ddg_after_attack(DDG* ddg, Stage* s, User* user);
          </div>
          <ul>
            <li><strong><code>render_ddg</code></strong>
              <ul>
                <li>피격 직후 60프레임 동안 <code>play_time - hit_time</code> 기준으로 깜빡이는 효과 적용</li>
                <li><code>al_draw_scaled_bitmap</code>으로 스프라이트 시트에서 100x100 영역을 잘라 <code>ddg_size</code>로 스케일링</li>
              </ul>
            </li>
            <li><strong><code>render_hud</code></strong>
              <ul>
                <li>DDG의 <code>life</code> 값만큼 하트 이미지를 화면 상단에 렌더</li>
              </ul>
            </li>
            <li><strong><code>update_ddg_after_attack</code></strong>
              <ul>
                <li>남은 체력이 1 초과면: 스테이지 시작 위치로 이동, life 감소</li>
                <li>마지막 생명이라면: <code>save_User(user)</code> (스테이지 &gt;1일 때), <code>after_stage</code>로 첫 페이지로 복귀</li>
                <li><code>ddg-&gt;hit_time = play_time</code>으로 피격 시점 기록</li>
              </ul>
            </li>
          </ul>
        </div>
      </section>

      <!-- 5. 지렁이 / 탄막 -->
      <section id="mod-worm" class="module-section">
        <h2>
          지렁이 / 탄막 시스템
          <span class="section-tag">for_worm · LIB_c_worm · LIB_shot</span>
        </h2>
        <p class="section-intro">
          맵 위를 이동하는 지렁이(<code>worm</code>)와 탄막을 발사하는 지렁이(<code>C_WORM</code>), 그리고 탄막 시스템(<code>SHOT_SYSTEM</code>)을 설명합니다.
        </p>

        <h3>이동형 지렁이 (for_worm)</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">worm* init_worm(...)</div>
            <div class="api-kind">적 이동 오브젝트</div>
          </div>
          <div class="api-signature">
#define WORM_SIZE         50
#define WORM_SPEED_STAGE1 5
#define WORM_SPEED_STAGE2 10
#define WORM_SPEED_STAGE3 3

enum WormType { HORIZONTAL = 0, VERTICAL = 1, SQUARE = 2 };

worm* init_worm(int x, int y, int lx, int rx, int ty, int by, int type, int speed, int dir);
void  update_worm(worm* w);
void  render_worm(worm* w);
bool  col_worms(DDG* ddg, int wormNum, worm** worms);
          </div>
          <ul>
            <li><strong>init_worm</strong>
              <ul>
                <li>이미지: <code>realWorm.png</code></li>
                <li><code>x,y</code>: 초기 좌표, <code>lx,rx,ty,by</code>는 이동 가능한 범위</li>
                <li><code>type</code>: 수평/수직/사각형 이동 타입</li>
              </ul>
            </li>
            <li><strong>update_worm</strong>
              <ul>
                <li><code>HORIZONTAL</code>: x축을 <code>speed * dir</code>만큼 이동, 범위 넘으면 방향 반전</li>
                <li><code>VERTICAL</code>: y축을 이동, 위/아래 경계에서 방향 반전</li>
              </ul>
            </li>
            <li><strong><code>col_worms</code></strong>
              <ul>
                <li>DDG의 사각형 영역과 모든 웜의 사각형 영역을 비교해 하나라도 겹치면 true</li>
              </ul>
            </li>
          </ul>
        </div>

        <h3>탄막 시스템 (LIB_shot)</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">SHOT_SYSTEM</div>
            <div class="api-kind">탄막 풀 관리</div>
          </div>
          <div class="api-signature">
#define SHOTS_N        128
#define C_WORM_SHOT_W   20
#define C_WORM_SHOT_H   20

typedef struct SHOT {
    int x, y;
    int dx, dy;
    int frame;
    bool used;
} SHOT;

typedef struct SHOT_SYSTEM {
    ALLEGRO_BITMAP* img;
    SHOT shots[SHOTS_N];
} SHOT_SYSTEM;

SHOT_SYSTEM* init_shots(const char* img_path);
bool         shots_add(SHOT_SYSTEM* s, int x, int y, int dx, int dy);
void         shots_update(SHOT_SYSTEM* s);
void         shots_draw(SHOT_SYSTEM* s);
bool         shots_collide_player(SHOT_SYSTEM* s, int x, int y, int w, int h);
          </div>
          <ul>
            <li><strong>init_shots</strong>: 탄막 비트맵을 로드하고 shot 배열을 초기화합니다.</li>
            <li><strong>shots_add</strong>: 사용 중이 아닌 슬롯을 찾아 위치/속도/프레임을 세팅하고 활성화합니다.</li>
            <li><strong>shots_update</strong>
              <ul>
                <li><code>dx, dy</code>만큼 이동하고, 화면 밖(<code>DISP_W, DISP_H</code>)으로 나가면 비활성화</li>
              </ul>
            </li>
            <li><strong>shots_collide_player</strong>: 플레이어 사각형과 각 샷 사각형의 충돌 여부를 검사하고, 충돌 시 해당 샷을 비활성화 후 true 반환.</li>
          </ul>
        </div>

        <h3>탄막 지렁이 (LIB_c_worm)</h3>
        <div class="api-card">
          <div class="api-header">
            <div class="api-name">C_WORM</div>
            <div class="api-kind">탄막 발사 적</div>
          </div>
          <div class="api-signature">
#define C_WORM_W 60
#define C_WORM_H 60

typedef struct C_WORM {
    ALLEGRO_BITMAP* img;
    int x, y;
    int w, h;
    int shot_timer;
    SHOT_SYSTEM* shots;
} C_WORM;

C_WORM* init_c_worm(int x, int y);
void    update_c_worm(C_WORM* worm);
void    render_c_worm(C_WORM* worm);
          </div>
          <ul>
            <li><strong>init_c_worm</strong>
              <ul>
                <li>이미지: <code>c_worm.png</code>, 탄막 이미지: <code>worm_shot.png</code></li>
                <li>초기 위치와 크기 설정, <code>shot_timer</code> 0으로 시작</li>
              </ul>
            </li>
            <li><strong>update_c_worm</strong>
              <ul>
                <li><code>shot_timer</code>가 0이 되면 왼쪽 방향으로 탄막 발사(<code>shots_add</code>)</li>
                <li>발사 후 <code>FIRE_DELAY</code> 만큼 쿨타임 설정</li>
                <li>매 프레임 <code>shots_update</code> 호출</li>
              </ul>
            </li>
            <li><strong>Stage3와 연동</strong>
              <ul>
                <li><code>col_c_worm_shots</code>에서 각 <code>C_WORM</code>의 탄막과 DDG 충돌을 검사</li>
              </ul>
            </li>
          </ul>
        </div>
      </section>

      <!-- 6. 꽃 아이템 -->
      <section id="mod-flower" class="module-section">
        <h2>
          꽃 아이템 시스템
          <span class="section-tag">for_flower.c / for_flower.h</span>
        </h2>
        <p class="section-intro">
          특정 스테이지에서 수집해야 하는 꽃 오브젝트를 관리합니다. Stage2/3의 클리어 조건과 직접적으로 연결됩니다.
        </p>

        <div class="api-card">
          <div class="api-header">
            <div class="api-name">flower 구조체</div>
            <div class="api-kind">수집 오브젝트</div>
          </div>
          <div class="api-signature">
#define FLOWER_SIZE 60

typedef struct flower {
    ALLEGRO_BITMAP* img;
    int x, y;
    int w, h;
    bool used;
} flower;

flower* init_flower(int x, int y);
void    update_flower(flower* f, DDG* ddg, Stage* s);
void    render_flower(flower* f);
          </div>
          <ul>
            <li><strong>init_flower</strong>
              <ul>
                <li>이미지: <code>flower.png</code></li>
                <li>주어진 타일 좌표 근처에 위치(x,y)와 이미지 크기(w,h)를 설정</li>
                <li><code>used = 0</code>으로 아직 수집되지 않은 상태로 시작</li>
              </ul>
            </li>
            <li><strong>update_flower</strong>
              <ul>
                <li>이미 수집(<code>used == 1</code>) 상태면 아무 작업도 하지 않음</li>
                <li>DDG와의 거리 기반 <code>collide</code> 함수를 사용해 일정 반경(30픽셀) 안이면 수집 처리</li>
                <li>수집 시 꽃 사운드(<code>ddg-&gt;flowerSound</code>) 재생 및 <code>s-&gt;flower_cnt--</code></li>
              </ul>
            </li>
            <li><strong>render_flower</strong>
              <ul>
                <li><code>used == 0</code>일 때만 화면에 그려짐</li>
              </ul>
            </li>
          </ul>
        </div>
      </section>

      <!-- 7. 유저 / 랭킹 -->
      <section id="mod-user" class="module-section">
        <h2>
          유저 · 랭킹 시스템
          <span class="section-tag">for_user.c / for_user.h</span>
        </h2>
        <p class="section-intro">
          플레이어 이름, 최고 스테이지, 클리어 타임을 관리하고 <code>ranking.txt</code> 파일로 저장/불러오기 하는 모듈입니다.
        </p>

        <div class="api-card">
          <div class="api-header">
            <div class="api-name">User 구조체</div>
            <div class="api-kind">유저 정보</div>
          </div>
          <div class="api-signature">
typedef struct {
    char name[21];  // 닉네임 (최대 20자 + '\0')
    int  stage;     // 깬 스테이지 번호
    int  time;      // 해당 스테이지를 깼을 때의 시간
} User;

User* init_User(void);
void  set_User(User* u, char* name, int stage, int time);
          </div>
          <ul>
            <li><strong><code>init_User</code></strong>: 이름을 빈 문자열로, stage/time을 0으로 초기화.</li>
            <li><strong><code>set_User</code></strong>
              <ul>
                <li>이름이 NULL이 아닐 경우 <code>name</code> 복사</li>
                <li>stage와 time 업데이트 후 디버그용 메시지를 출력</li>
              </ul>
            </li>
          </ul>
        </div>

        <div class="api-card">
          <div class="api-header">
            <div class="api-name">랭킹 저장 / 로드</div>
            <div class="api-kind">파일 I/O</div>
          </div>
          <div class="api-signature">
void save_User(User* u);
int  load_top_Users(User* Users, int max_count);
void draw_top_Users(ALLEGRO_FONT* font);
void print_all_Users(void);
          </div>
          <ul>
            <li><strong><code>save_User</code></strong>
              <ul>
                <li><code>ranking.txt</code>를 읽어 기존 기록을 메모리에 로드</li>
                <li>같은 이름이 있으면 stage가 더 크거나, 같은 stage에 time이 더 짧을 때 교체</li>
                <li>없는 이름이면 최대 고정 크기까지 추가</li>
                <li>stage 내림차순, time 오름차순으로 정렬 후 다시 파일에 저장</li>
              </ul>
            </li>
            <li><strong><code>draw_top_Users</code></strong>
              <ul>
                <li>파일에서 상위 랭킹들을 읽어 지정된 폰트로 첫 페이지에 텍스트를 렌더링</li>
                <li>초 &lt; 60일 때와 그 이상일 때 분/초 표기를 다르게 표시</li>
              </ul>
            </li>
          </ul>
        </div>
      </section>

      <!-- 8. 첫 화면 / 설명 페이지 -->
      <section id="mod-firstpage" class="module-section">
        <h2>
          첫 화면 · 설명 페이지
          <span class="section-tag">LIB_first_page</span>
        </h2>
        <p class="section-intro">
          플레이 시작 전 이름 입력 화면, 랭킹 표시, 조작 설명 화면(Explanation Page)을 구현하는 모듈입니다.
        </p>

        <div class="api-card">
          <div class="api-header">
            <div class="api-name">void run_first_page(User* user, SYSTEM* sys, ALLEGRO_EVENT ev)</div>
            <div class="api-kind">첫 페이지 루프</div>
          </div>
          <div class="api-signature">
void draw_scaled_crop(ALLEGRO_BITMAP* image);
void run_first_page(User* user, SYSTEM* sys, ALLEGRO_EVENT ev);
void run_explanation_page(ALLEGRO_EVENT ev);
          </div>
          <ul>
            <li><strong><code>run_first_page</code> 동작</strong>
              <ul>
                <li>리소스를 한 번만 로드: <code>page.png</code> 배경, 랭킹 폰트</li>
                <li>키 입력 이벤트(<code>ALLEGRO_EVENT_KEY_CHAR</code>)를 사용해 이름 문자열을 작성</li>
                <li>엔터를 누르면
                  <ul>
                    <li><code>set_User(user, user_name, 0, 0)</code>으로 유저 이름 세팅</li>
                    <li>설명 페이지를 아직 보지 않았다면 <code>MODE_EXPLAIN</code>으로, 이미 봤다면 바로 Stage1 세팅(<code>MODE_SET_STAGE1</code>)으로 이동</li>
                  </ul>
                </li>
                <li>타이머 이벤트 시 배경과 이름, <code>draw_top_Users</code>로 랭킹 표시</li>
              </ul>
            </li>
            <li><strong><code>run_explanation_page</code></strong>
              <ul>
                <li>설명용 배경(<code>explanation_bg.png</code>)을 한 번만 로드</li>
                <li>SPACE 키를 누르면 스테이지1 세팅 모드(<code>MODE_SET_STAGE1</code>)로 전환</li>
              </ul>
            </li>
          </ul>
        </div>
      </section>

    </div>
  </section>
</main>

<footer>
  <div>두근두근 두더지의 프러포즈 작전 &mdash; 실제 프로젝트 코드 기반 API 문서</div>
  <div>모듈 버튼을 눌러 각 서브 시스템의 API를 확인할 수 있습니다.</div>
</footer>

<script>
  (function() {
    const buttons = document.querySelectorAll('.module-btn');
    const sections = document.querySelectorAll('.module-section');

    function activate(targetId) {
      sections.forEach(sec => {
        sec.classList.toggle('active', sec.id === targetId);
      });
      buttons.forEach(btn => {
        btn.classList.toggle('active', btn.dataset.target === targetId);
      });
    }

    buttons.forEach(btn => {
      btn.addEventListener('click', () => {
        activate(btn.dataset.target);
      });
    });

    // 첫 로드시 개요 섹션 활성
    activate('mod-overview');
  })();
</script>
</body>
</html>
