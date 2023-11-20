'use strict';

const { AudioContext } = require('..');


(async () => { try {
	
	const context = new AudioContext();
	
	const oscillator1 = context.createOscillator();
	const oscillator2 = context.createOscillator();
	
	const gain = context.createGain();
	gain.gain.value = 0.5;
	
	// osc . gain . destination
	oscillator1.connect(gain);
	oscillator2.connect(gain);
	gain.connect(context.destination);
	
	oscillator1.type = 'sine';
	oscillator1.frequency.value = 220;
	oscillator1.start(0);
	
	oscillator2.type = 'sine';
	oscillator2.frequency.value = 440;
	oscillator2.start(0);
	
	
	for (let i = 0; i < 10; i++) {
		oscillator1.disconnect();
		oscillator2.connect(gain);
		await new Promise((res) => setTimeout(res, 200));
		
		oscillator2.disconnect();
		oscillator1.connect(gain);
		await new Promise((res) => setTimeout(res, 200));
	}
	
	oscillator1.disconnect();
	oscillator2.disconnect();
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();

