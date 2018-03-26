'use strict';

const { AudioContext, OscillatorNode } = require('..');


(async () => { try {
	
	console.log('index.js', 'ty', typeof AudioContext);
	const context = new AudioContext();
	console.log('index.js', 'CC', context);
	// console.log('index.js', 'SUS');
	// context.suspend();
	// console.log('index.js', 'SUS OK');
	console.log('index.js', context.state);
	
	const oscillator1 = context.createOscillator();
	const oscillator2 = context.createOscillator();
	console.log('index.js', 'OSC', oscillator1, oscillator1 instanceof OscillatorNode);
	const gain = context.createGain();
	console.log('index.js', 'GAIN1');
	// console.log('gain', context.createGain);
	gain.gain.value = 0.5;
	console.log('index.js', 'GAIN2');
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
	
	
	// for (let i = 0; i < 10; i++) {
	// 	console.log('i', i);
	// 	context.disconnect(null, oscillator1, 0, 0);
	// 	context.connect(gain, oscillator2, 0, 0);
	// 	await new Promise(res => setTimeout(res, 200));
		
	// 	context.disconnect(null, oscillator2, 0, 0);
	// 	context.connect(gain, oscillator1, 0, 0);
	// 	await new Promise(res => setTimeout(res, 200));
	// }
	
	// context.disconnect(null, oscillator1, 0, 0);
	// context.disconnect(null, oscillator2, 0, 0);
	
	// context.reset();
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();

