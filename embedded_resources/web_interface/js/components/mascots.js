ï»¿/**
 * ââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Â
 * lele - Mascot System with Sprites
 * Lele mascot with multiple mood sprites
 * ââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Âââ¢Â
 */

const MascotSystem = {
    // Sprite paths for Lele
    spritePath: '/sprites/lele/',

    mascots: {
        lele: {
            name: 'Lele',
            emoji: '°Å¸âÂ¦',
            sprite: 'lele_idle.png',
            moods: {
                idle: { emoji: '°Å¸âÂ¦', sprite: 'lele_idle.png' },
                happy: { emoji: '°Å¸Ëâ', sprite: 'lele_happy_1.png' },
                hunting: { emoji: '°Å¸Â§Â', sprite: 'lele_idle_2.png' },
                angry: { emoji: '°Å¸ËÂ ', sprite: 'lele_sad.png' },
                sleeping: { emoji: '°Å¸ËÂ´', sprite: 'lele_sleep_1.png' },
                attacking: { emoji: '°Å¸ËÅ½', sprite: 'lele_attack.png' },
                success: { emoji: 'âÅÅÃ¯Â¸Â', sprite: 'lele_happy_2.png' },
                alert: { emoji: '°Å¸ËÂ³', sprite: 'lele_motivated.png' },
                cool: { emoji: '°Å¸ËÅ½', sprite: 'lele_cool.png' }
            },
            phrases: {
                idle: ['E aÃÂ­, beleza?', 'Tudo tranquilo?', 'Bora mexer nesses pacotes?', 'TÃÂ´ pronto, e vocÃÂª?'],
                hunting: ['Olhando quem tÃÂ¡ perto...', 'Escaneando...', 'Hum, rede interessante...', 'Xiii, achei algo.'],
                success: ['AÃÂ­ sim! Pegamos!', 'Sucesso total!', 'TÃÂ¡ na mÃÂ£o!', 'Handshake capturado! °Å¸ââ'],
                attack: ['Hora do show!', 'Segura essa!', 'Enviando pacotes...', 'Deauth ativado!'],
                sleep: ['Vou dar um cochilo...', 'Zzz...', 'AtÃÂ© mais...', 'Modo economia...']
            },
            color: '#00fff5'
        }
    },

    currentMascot: 'lele',
    currentMood: 'idle',
    useSprites: true, // Toggle between emoji and sprite mode

    init() {
        const saved = localStorage.getItem('lele-mascot');
        if (saved && this.mascots[saved]) {
            this.currentMascot = saved;
        }
        this.render();
        console.log('[Mascot] lele mascot system initialized');
    },

    setMascot(mascotId) {
        if (!this.mascots[mascotId]) {
            console.warn(`[Mascot] Unknown mascot: ${mascotId}, defaulting to lele`);
            mascotId = 'lele';
        }
        this.currentMascot = mascotId;
        localStorage.setItem('lele-mascot', mascotId);
        this.render();
        console.log(`[Mascot] Changed to: ${this.mascots[mascotId].name}`);

        // Sync with Firmware
        let id = 1; // Lele ID
        fetch('/api/mascot/select', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: `id=${id}`
        }).then(() => {
            console.log("[Mascot] Synced with firmware");
        }).catch(e => console.error("[Mascot] Sync failed", e));
    },

    setMood(mood) {
        const mascot = this.mascots[this.currentMascot];
        if (mascot && mascot.moods[mood]) {
            this.currentMood = mood;
            this.render();
        }
    },

    getRandomPhrase(type = 'idle') {
        const mascot = this.mascots[this.currentMascot];
        const phrases = mascot.phrases[type] || mascot.phrases.idle;
        return phrases[Math.floor(Math.random() * phrases.length)];
    },

    render() {
        const mascot = this.mascots[this.currentMascot];
        if (!mascot) return;

        const moodData = mascot.moods[this.currentMood] || mascot.moods.idle;

        // Update avatar - check for image element first, then emoji
        const avatarImg = document.getElementById('mascot-sprite');
        const avatarEmoji = document.getElementById('dragon-avatar') || document.getElementById('mascot-avatar');

        if (avatarImg && this.useSprites) {
            avatarImg.src = this.spritePath + moodData.sprite;
            avatarImg.style.display = 'block';
            if (avatarEmoji) avatarEmoji.style.display = 'none';
        } else if (avatarEmoji) {
            avatarEmoji.textContent = moodData.emoji;
            avatarEmoji.style.filter = `drop-shadow(0 0 20px ${mascot.color})`;
            if (avatarImg) avatarImg.style.display = 'none';
        }

        // Update name
        const nameEl = document.getElementById('dragon-name') || document.getElementById('mascot-name');
        if (nameEl) {
            nameEl.textContent = mascot.name;
            nameEl.style.color = mascot.color;
        }

        // Update bubble
        const bubble = document.getElementById('dragon-bubble') || document.getElementById('mascot-bubble');
        if (bubble) {
            bubble.textContent = this.getRandomPhrase(this.currentMood);
            bubble.style.borderColor = mascot.color;
        }

        // Update selector if exists
        const selector = document.getElementById('mascot-selector');
        if (selector) {
            selector.value = this.currentMascot;
        }
    },

    react(event) {
        const reactions = {
            'handshake': { mood: 'success', reset: 'happy', delay: 3000 },
            'attack_start': { mood: 'attacking' },
            'attack_stop': { mood: 'idle' },
            'scan': { mood: 'hunting' },
            'error': { mood: 'angry', reset: 'idle', delay: 2000 },
            'sleep': { mood: 'sleeping' }
        };

        const reaction = reactions[event];
        if (reaction) {
            this.setMood(reaction.mood);
            if (reaction.reset) {
                setTimeout(() => this.setMood(reaction.reset), reaction.delay);
            }
        } else {
            this.setMood('idle');
        }
    },

    // Toggle between sprite and emoji mode
    toggleSpriteMode() {
        this.useSprites = !this.useSprites;
        this.render();
        console.log(`[Mascot] Sprite mode: ${this.useSprites}`);
    },

    getAll() {
        return Object.entries(this.mascots).map(([id, mascot]) => ({
            id,
            name: mascot.name,
            emoji: mascot.emoji,
            color: mascot.color
        }));
    }
};

// Initialize on load
document.addEventListener('DOMContentLoaded', () => {
    MascotSystem.init();
});

// Exports
window.MascotSystem = MascotSystem;
window.setMascot = (id) => MascotSystem.setMascot(id);
window.mascotReact = (event) => MascotSystem.react(event);

