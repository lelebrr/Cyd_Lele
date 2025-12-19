
// ==========================================
// SIMULATION MODE (Visuals only)
// ==========================================
function simulateTraffic() {
    console.log('[SIM] Starting visual simulation...');

    setInterval(() => {
        // Random Signal
        const signal = -40 - Math.random() * 50;
        updateChart('signal', signal);

        // Random Channel updates
        if (Math.random() > 0.8) {
            const ch = Math.floor(Math.random() * 13);
            if (WavePwn.charts.channel) {
                WavePwn.charts.channel.data.datasets[0].data[ch] = Math.floor(Math.random() * 20);
                WavePwn.charts.channel.update('none');
            }
        }

        // Random Log
        if (Math.random() > 0.95) {
            const msgs = ['[SCAN] Found hidden network: FBI_Surveillance_Van', '[BLE] New device: Apple iPhone 14', '[RF] Signal detected: 433.92MHz', '[SYSTEM] Memory optimization...'];
            const msg = msgs[Math.floor(Math.random() * msgs.length)];
            const logContainer = document.getElementById('log-container');
            if (logContainer) {
                const div = document.createElement('div');
                div.style.color = 'cyan';
                div.textContent = msg;
                logContainer.prepend(div);
                if (logContainer.children.length > 20) logContainer.lastChild.remove();
            }
        }

    }, 1000);
}
