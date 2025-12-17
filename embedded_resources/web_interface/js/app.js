/**
 * â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
 * WAVEPWN - Main Application Entry Point
 * â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
 */

// Global state
const WavePwn = {
    state: {
        connected: false,
        theme: 'cyberpunk',
        soundEnabled: true,
        currentView: 'dashboard',
        stats: {
            uptime: 0,
            battery: 0,
            networks: 0,
            handshakes: 0,
            pmkids: 0,
            bleDevices: 0,
            deauthsSent: 0,
            temperature: 0
        },
        dragon: {
            name: 'Neura',
            mood: 'happy',
            personality: 'aggressive'
        }
    },
    ws: null,
    charts: {},
    sounds: {}
};

// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
// INITIALIZATION
// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
document.addEventListener('DOMContentLoaded', () => {
    console.log('[Lele] Initializing Cyberpunk Command Center...');

    // Show boot animation
    showBootAnimation().then(() => {
        // Initialize all modules
        initTheme();
        initWebSocket();

        // Load Mascot State (Syncs Avatar/Boot/Sidebar)
        if (typeof loadMascotState === 'function') {
            loadMascotState().then(() => {
                // Only init Dragon logic if Dragon is active
                // (initDragon check inside dragon.js handles this, but we force correct order)
                initDragon();
            });
        } else {
            initDragon();
        }

        initEffects();
        initNavigation();
        initEasterEggs();
        initGlitchButtons();
        initCharts();

        // Show initial view
        showView('dashboard');

        console.log('[Lele] Initialization complete!');
    });
});

// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
// BOOT ANIMATION
// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
async function showBootAnimation() {
    return new Promise((resolve) => {
        const overlay = document.getElementById('boot-overlay');
        if (!overlay) {
            resolve();
            return;
        }

        const bootText = overlay.querySelector('.boot-text');
        const bootLines = [
            'Lele SYSTEM INITIALIZING...',
            'LOADING NEURAL NETWORKS...',
            'CONNECTING TO Lele CORE...',
            'ESTABLISHING SECURE CHANNEL...',
            'SYSTEM READY.'
        ];

        let lineIndex = 0;
        const lineInterval = setInterval(() => {
            if (lineIndex < bootLines.length) {
                bootText.innerHTML += bootLines[lineIndex] + '<br>';
                lineIndex++;
            } else {
                clearInterval(lineInterval);
            }
        }, 400);

        // Fade out after boot completes
        setTimeout(() => {
            overlay.classList.add('fade-out');
            setTimeout(() => {
                overlay.style.display = 'none';
                resolve();
            }, 1000);
        }, 2500);
    });
}

// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
// THEME SYSTEM
// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
function initTheme() {
    const savedTheme = localStorage.getItem('wavepwn-theme') || 'cyberpunk';
    setTheme(savedTheme);
}

function setTheme(themeName) {
    document.documentElement.setAttribute('data-theme', themeName);
    WavePwn.state.theme = themeName;
    localStorage.setItem('wavepwn-theme', themeName);

    // Update theme selector if exists
    const selector = document.getElementById('theme-selector');
    if (selector) selector.value = themeName;

    console.log(`[Theme] Switched to: ${themeName}`);
}

function toggleNightOps() {
    document.body.classList.toggle('night-ops');

    // Create night ops dot if needed
    if (document.body.classList.contains('night-ops')) {
        if (!document.querySelector('.night-ops-dot')) {
            const dot = document.createElement('div');
            dot.classList.add('night-ops-dot');
            document.body.appendChild(dot);
        }
    }
}

// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
// MOBILE SIDEBAR - Definido primeiro para garantir disponibilidade
// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•

// Mobile sidebar toggle function (global) - DEVE SER DEFINIDA ANTES DE SER USADA
function toggleSidebar() {
    console.log('[MENU] toggleSidebar chamado');
    const sidebar = document.getElementById('sidebar');
    const overlay = document.querySelector('.sidebar-overlay');

    if (!sidebar) {
        console.error('[MENU] ERRO: elemento #sidebar nÃ£o encontrado!');
        return;
    }

    const wasOpen = sidebar.classList.contains('open');
    console.log('[MENU] Estado antes:', wasOpen ? 'ABERTO' : 'FECHADO');

    if (wasOpen) {
        sidebar.classList.remove('open');
        if (overlay) overlay.classList.remove('active');
        console.log('[MENU] Fechando sidebar');
    } else {
        sidebar.classList.add('open');
        if (overlay) overlay.classList.add('active');
        console.log('[MENU] Abrindo sidebar');
    }

    console.log('[MENU] Estado depois:', sidebar.classList.contains('open') ? 'ABERTO' : 'FECHADO');
}

// Fechar sidebar ao clicar em um item do menu (mobile)
function closeSidebarOnNavClick() {
    if (window.innerWidth <= 768) {
        const sidebar = document.getElementById('sidebar');
        const overlay = document.querySelector('.sidebar-overlay');

        if (sidebar) sidebar.classList.remove('open');
        if (overlay) overlay.classList.remove('active');
    }
}

// Expor toggleSidebar globalmente IMEDIATAMENTE
window.toggleSidebar = toggleSidebar;

// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
// NAVIGATION
// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
function initNavigation() {
    const navLinks = document.querySelectorAll('.nav-links a, .nav-links button');

    navLinks.forEach(link => {
        link.addEventListener('click', (e) => {
            e.preventDefault();
            const viewId = link.dataset.view || link.getAttribute('href')?.replace('#', '');
            if (viewId) {
                showView(viewId);

                // Update active state
                navLinks.forEach(l => l.classList.remove('active'));
                link.classList.add('active');

                // Fechar sidebar em mobile apÃ³s clicar em um item do menu
                closeSidebarOnNavClick();
            }
        });
    });

    // Mobile sidebar toggle - usar toggleSidebar para consistÃªncia
    const menuToggle = document.getElementById('mobile-menu-btn');
    if (menuToggle) {
        menuToggle.addEventListener('click', toggleSidebar);
    }

    // Overlay click para fechar sidebar
    const overlay = document.querySelector('.sidebar-overlay');
    if (overlay) {
        overlay.addEventListener('click', toggleSidebar);
    }
}

// Placeholder for init() and loadMascotState() from the instruction,
// assuming they are methods of a global app object (e.g., WavePwn)
// and the instruction snippet was incomplete or out of context for top-level functions.
// Given the existing structure, these would likely be top-level functions or
// methods of a specific module. For now, I'll place them as top-level functions
// as the instruction implies they are new functions to be added.
// Note: The `this` references in the instruction's `init()` suggest it's a method
// of an object, but without that object's definition, it's hard to place correctly.
// I will define them as standalone functions for syntactic correctness based on the surrounding code.

// Assuming init() and loadMascotState() are part of a larger app object,
// but for this edit, they are placed as standalone functions as per the instruction's context.
// The `this` references in the instruction's `init()` would require a different
// code structure (e.g., a class or an object literal for the main app).
// For now, I'll define the `loadMascotState` function as requested.
// The `init()` function from the instruction seems to be a different initialization
// routine than the existing `DOMContentLoaded` one, and contains `this` references
// that don't fit the current global function pattern. I will only add `loadMascotState`
// as it's a complete, self-contained function.

async function loadMascotState() {
    try {
        const res = await fetch('/api/mascot/current');
        const data = await res.json();
        let mascotId = 'dragon';
        if (data.id === 1) mascotId = 'lele';
        if (data.id === 2) mascotId = 'lisa';

        if (window.MascotSystem) {
            window.MascotSystem.setMascot(mascotId);
            // Force UI update
            // const bootMascot = document.getElementById('boot-mascot'); // Removido: Agora usamos logo.png estÃ¡tico
            const sidebarMascot = document.getElementById('sidebar-mascot');
            // if (bootMascot) bootMascot.textContent = window.MascotSystem.mascots[mascotId].emoji;
            if (sidebarMascot) sidebarMascot.textContent = window.MascotSystem.mascots[mascotId].emoji;
        }
    } catch (e) { console.warn("Mascot sync failed", e); }
}


function showView(viewId) {
    // Glitch-scan transition effect (hacker style)
    const transition = document.createElement('div');
    transition.className = 'glitch-scan-transition';
    transition.innerHTML = `
        <div class="scan-line"></div>
        <div class="glitch-bars">
            <div class="glitch-bar"></div>
            <div class="glitch-bar"></div>
            <div class="glitch-bar"></div>
        </div>
    `;
    document.body.appendChild(transition);

    // Phase 1: Glitch scan in
    setTimeout(() => {
        // Hide all views
        document.querySelectorAll('.view').forEach(view => {
            view.classList.remove('active');
        });

        // Show target view
        const targetView = document.getElementById(viewId);
        if (targetView) {
            targetView.classList.add('active');
            WavePwn.state.currentView = viewId;
        }

        // Phase 2: Scan out
        transition.classList.add('scan-out');

        setTimeout(() => {
            transition.remove();
        }, 300);
    }, 250);
}

function showAchievement(achievement) {
    const toast = document.createElement('div');
    toast.className = 'achievement-toast';
    toast.innerHTML = `
        <div class="achievement-icon">ðŸ†</div>
        <div class="achievement-content">
            <div class="achievement-title">${achievement.title}</div>
            <div class="achievement-desc">${achievement.description}</div>
        </div>
    `;
    document.body.appendChild(toast);

    // Trigger border notification for achievement
    if (typeof triggerBorderNotification === 'function') {
        triggerBorderNotification('#FFCC00', 4); // Rainbow effect for achievements
    }

    setTimeout(() => {
        toast.classList.add('show');
    }, 100);

    setTimeout(() => {
        toast.classList.remove('show');
        setTimeout(() => toast.remove(), 500);
    }, 5000);
}

function showToast(message, type = 'info', duration = 3000) {
    const toast = document.createElement('div');
    toast.className = `toast toast-${type}`;
    toast.textContent = message;

    // Add icon based on type
    if (type === 'error') toast.innerHTML = 'âŒ ' + message;
    if (type === 'success') toast.innerHTML = 'âœ… ' + message;
    if (type === 'warning') toast.innerHTML = 'âš ï¸ ' + message;
    if (type === 'info') toast.innerHTML = 'â„¹ï¸ ' + message;

    document.body.appendChild(toast);

    setTimeout(() => {
        toast.classList.add('show');
    }, 100);

    setTimeout(() => {
        toast.classList.remove('show');
        setTimeout(() => toast.remove(), 500);
    }, duration);
}

window.showToast = showToast;

// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
// GLITCH BUTTON EFFECT
// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
function initGlitchButtons() {
    document.querySelectorAll('.btn, button').forEach(btn => {
        btn.addEventListener('click', function () {
            this.classList.add('glitch-click-active');

            // Play click sound if enabled
            if (WavePwn.state.soundEnabled && WavePwn.sounds.click) {
                WavePwn.sounds.click.play();
            }

            setTimeout(() => {
                this.classList.remove('glitch-click-active');
            }, 300);
        });
    });
}

// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
// EFFECTS
// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
function initEffects() {
    // Initialize Matrix rain
    initMatrixRain();

    // Initialize floating particles
    initParticles();

    // Add scanlines overlay
    if (!document.querySelector('.scanlines-overlay')) {
        const scanlines = document.createElement('div');
        scanlines.classList.add('scanlines-overlay');
        document.body.appendChild(scanlines);
    }
}

// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
// CHARTS
// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
function initCharts() {
    // Signal strength chart
    const signalCanvas = document.getElementById('signal-chart');
    if (signalCanvas && typeof Chart !== 'undefined') {
        WavePwn.charts.signal = new Chart(signalCanvas, {
            type: 'line',
            data: {
                labels: Array(30).fill(''),
                datasets: [{
                    label: 'Atividade WiFi',
                    data: Array(30).fill(0),
                    borderColor: getComputedStyle(document.documentElement).getPropertyValue('--primary').trim(),
                    backgroundColor: 'rgba(0, 255, 245, 0.1)',
                    tension: 0.4,
                    fill: true,
                    pointRadius: 0
                }]
            },
            options: {
                responsive: true,
                maintainAspectRatio: false,
                plugins: { legend: { display: false } },
                scales: {
                    y: {
                        beginAtZero: true,
                        grid: { color: 'rgba(255,255,255,0.05)' },
                        ticks: { color: '#606070' }
                    },
                    x: { display: false }
                },
                animation: { duration: 0 }
            }
        });
    }

    // Channel usage chart
    const channelCanvas = document.getElementById('channel-chart');
    if (channelCanvas && typeof Chart !== 'undefined') {
        WavePwn.charts.channel = new Chart(channelCanvas, {
            type: 'bar',
            data: {
                labels: ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13'],
                datasets: [{
                    label: 'APs por Canal',
                    data: Array(13).fill(0),
                    backgroundColor: 'rgba(0, 255, 245, 0.6)',
                    borderColor: '#00fff5',
                    borderWidth: 1
                }]
            },
            options: {
                responsive: true,
                maintainAspectRatio: false,
                plugins: { legend: { display: false } },
                scales: {
                    y: {
                        beginAtZero: true,
                        grid: { color: 'rgba(255,255,255,0.05)' },
                        ticks: { color: '#606070' }
                    },
                    x: {
                        grid: { display: false },
                        ticks: { color: '#606070' }
                    }
                }
            }
        });
    }

    // Security type pie chart
    const securityCanvas = document.getElementById('security-chart');
    if (securityCanvas && typeof Chart !== 'undefined') {
        WavePwn.charts.security = new Chart(securityCanvas, {
            type: 'doughnut',
            data: {
                labels: ['WPA2', 'WPA3', 'WEP', 'Open'],
                datasets: [{
                    data: [0, 0, 0, 0],
                    backgroundColor: ['#00fff5', '#ff00ff', '#ffcc00', '#ff0055'],
                    borderWidth: 0
                }]
            },
            options: {
                responsive: true,
                maintainAspectRatio: false,
                plugins: {
                    legend: {
                        position: 'bottom',
                        labels: { color: '#a0a0b0' }
                    }
                }
            }
        });
    }
}

function updateChart(chartName, newValue) {
    const chart = WavePwn.charts[chartName];
    if (!chart) return;

    if (chartName === 'signal') {
        chart.data.datasets[0].data.push(newValue);
        chart.data.datasets[0].data.shift();
        chart.update('none');
    }
}

// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
// SOUND EFFECTS
// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
function initSounds() {
    // Only load if sounds are enabled and available
    try {
        WavePwn.sounds.kaChng = new Audio('/assets/sounds/ka-ching.mp3');
        WavePwn.sounds.click = new Audio('/assets/sounds/click.mp3');
        WavePwn.sounds.alert = new Audio('/assets/sounds/alert.mp3');
        WavePwn.sounds.ambient = new Audio('/assets/sounds/ambient.mp3');
        WavePwn.sounds.ambient.loop = true;
        WavePwn.sounds.ambient.volume = 0.2;
    } catch (e) {
        console.log('[Sound] Audio not available');
    }
}

function playKaChing() {
    if (WavePwn.state.soundEnabled && WavePwn.sounds.kaChng) {
        WavePwn.sounds.kaChng.currentTime = 0;
        WavePwn.sounds.kaChng.play().catch(() => { });
    }
}

function toggleAmbientSound() {
    if (!WavePwn.sounds.ambient) return;

    if (WavePwn.sounds.ambient.paused) {
        WavePwn.sounds.ambient.play().catch(() => { });
    } else {
        WavePwn.sounds.ambient.pause();
    }
}

// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
// UI UPDATE HELPERS
// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
function updateStats(data) {
    // Update internal state
    Object.assign(WavePwn.state.stats, data);

    // Update DOM elements
    updateElement('uptime', formatUptime(data.uptime));
    updateElement('battery', data.battery + '%');
    updateElement('temperature', data.temperature + 'Â°C');
    updateElement('networks-count', data.networks);
    updateElement('handshakes-count', data.handshakes, true);
    updateElement('pmkid-count', data.pmkids);
    updateElement('ble-count', data.bleDevices);
    updateElement('deauths-count', data.deauthsSent);

    // New system info fields
    updateElement('mac-wifi', data.macWifi);
    updateElement('mac-ble', data.macBle);

    // RAM/Heap info (in KB, display as formatted)
    if (data.heapTotal > 0) {
        const heapUsed = data.heapTotal - data.heapFree;
        updateElement('heap-free', data.heapFree + ' KB');
        updateElement('ram-used', Math.round((heapUsed / data.heapTotal) * 100) + '%');
    }

    // SD Card info
    if (data.sdOnline) {
        const sdFree = data.sdTotal - data.sdUsed;
        updateElement('sd-space', sdFree + ' / ' + data.sdTotal + ' MB');
    } else {
        updateElement('sd-space', 'NÃ£o inserido');
    }

    // Update threat indicator
    const threatEl = document.getElementById('threat-level');
    if (threatEl && data.threat) {
        threatEl.textContent = data.threat;
        threatEl.className = `threat-badge threat-${data.threat.toLowerCase()}`;
    }
}

function updateElement(id, value, animate = false) {
    const el = document.getElementById(id);
    if (!el) return;

    const oldValue = el.textContent;
    el.textContent = value;

    // Animate if value changed
    if (animate && oldValue !== String(value)) {
        el.classList.add('counter-update');
        setTimeout(() => el.classList.remove('counter-update'), 300);

        // Play ka-ching for handshakes
        if (id === 'handshakes-count' && parseInt(value) > parseInt(oldValue)) {
            playKaChing();
            el.classList.add('ka-ching');
            setTimeout(() => el.classList.remove('ka-ching'), 1000);
        }
    }
}

function formatUptime(seconds) {
    const h = Math.floor(seconds / 3600);
    const m = Math.floor((seconds % 3600) / 60);
    const s = seconds % 60;
    return `${h.toString().padStart(2, '0')}:${m.toString().padStart(2, '0')}:${s.toString().padStart(2, '0')}`;
}

function addLog(message, type = 'info') {
    const logContainer = document.getElementById('log-container');
    if (!logContainer) return;

    const logLine = document.createElement('div');
    logLine.classList.add('log-line', `log-${type}`);
    const time = new Date().toLocaleTimeString();
    logLine.innerHTML = `<span class="log-time">[${time}]</span> <span class="log-msg">${message}</span>`;

    logContainer.insertBefore(logLine, logContainer.firstChild);

    // Keep only last 100 logs
    while (logContainer.children.length > 100) {
        logContainer.removeChild(logContainer.lastChild);
    }
}

// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
// API COMMANDS
// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
async function sendCommand(command, params = {}) {
    console.log(`[CMD] Executing: ${command}`, params);

    // Send via WebSocket if connected
    if (WavePwn.ws && WavePwn.ws.readyState === WebSocket.OPEN) {
        WavePwn.ws.send(JSON.stringify({ cmd: command, ...params }));
        addLog(`Comando enviado: ${command}`, 'info');
        console.log(`[WS] Command sent via WebSocket: ${command}`);
        return;
    }

    // Log warning if WebSocket not connected
    console.warn(`[WS] WebSocket not connected (state: ${WavePwn.ws?.readyState ?? 'null'}), using HTTP fallback`);

    // Fallback to HTTP API
    try {
        const response = await fetch(`/api/${command}`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(params)
        });

        if (!response.ok) {
            throw new Error(`HTTP ${response.status}: ${response.statusText}`);
        }

        const data = await response.json();
        addLog(`${command}: ${data.status || 'OK'}`, 'success');
        console.log(`[API] HTTP response for ${command}:`, data);
        return data;
    } catch (error) {
        addLog(`Erro: ${error.message}`, 'error');
        console.error(`[API] Failed to execute ${command}:`, error);
        throw error;
    }
}

// Attack shortcuts
function startDeauth(target) {
    sendCommand('deauth', { target });
}

function startBeaconFlood() {
    sendCommand('beacon');
}

function startHandshakeCapture() {
    sendCommand('handshake');
}

function stopAllAttacks() {
    sendCommand('stop');
}

function pwnEverything() {
    const btn = document.getElementById('pwn-btn');
    if (!btn) return;

    // Countdown
    let countdown = 60;
    btn.disabled = true;
    btn.textContent = `PWN ATIVO: ${countdown}s`;
    btn.classList.add('active');

    // Start all attacks
    sendCommand('pwn_all');

    const interval = setInterval(() => {
        countdown--;
        btn.textContent = `PWN ATIVO: ${countdown}s`;

        if (countdown <= 0) {
            clearInterval(interval);
            sendCommand('stop');
            btn.disabled = false;
            btn.textContent = 'â˜ ï¸ PWN EVERYTHING â˜ ï¸';
            btn.classList.remove('active');
        }
    }, 1000);
}

// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
// EXPORTS
// â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
window.WavePwn = WavePwn;
window.showView = showView;
window.setTheme = setTheme;
window.toggleNightOps = toggleNightOps;
window.sendCommand = sendCommand;
window.startDeauth = startDeauth;
window.startBeaconFlood = startBeaconFlood;
window.startHandshakeCapture = startHandshakeCapture;
window.stopAllAttacks = stopAllAttacks;
window.pwnEverything = pwnEverything;
window.toggleAmbientSound = toggleAmbientSound;
window.toggleSidebar = toggleSidebar;
window.closeSidebarOnNavClick = closeSidebarOnNavClick;

