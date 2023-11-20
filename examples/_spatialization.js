'use strict';

const { AudioContext } = require('..');

const { readAsBuffer } = require('./utils/read-as-buffer');


(async () => { try {
	
	const context = new AudioContext();
	
	const voice = await readAsBuffer(`${__dirname}/samples/voice.ogg`);
	
	const audioClip = await new Promise((res) => context.decodeAudioData(voice, (b) => res(b)));
	const audioClipNode = context.createBufferSource();
	audioClipNode.buffer = audioClip;
	
	const panner = context.createPanner();
	// panner.panningModel = 'HRTF';
	panner.connect(context.destination);
	
	audioClipNode.connect(panner);
	audioClipNode.start(0);
	audioClipNode.loop = true;
	
	context.listener.setPosition(0, 0, 0);
	
	for (let i = 0; i < 1000; i++) {
		
		const rad = Math.PI * i * 0.001;
		const r = 11 - i / 1000;
		const s = r * Math.sin(rad);
		const c = r * Math.cos(rad);
		
		panner.setVelocity(-s, 0, c); // derivative
		// panner.setPosition(c, 0, s);
		panner.positionX.value = c;
		panner.positionZ.value = s;
		
		// Wait
		await new Promise((res) => setTimeout(res, 15));
		
	}
	
	// for (let i = 0; i < 1000; i++) {
		
	// 	const rad = Math.PI * i * 0.001;
	// 	const r = 11 - i / 1000;
	// 	const s = r * Math.sin(rad);
	// 	const c = r * Math.cos(rad);
		
	// 	panner.setVelocity(-s, 0, c); // derivative
	// 	panner.setPosition(c, 0, s);
		
	// 	// Wait
	// 	await new Promise(res => setTimeout(res, 15));
		
	// }
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();

