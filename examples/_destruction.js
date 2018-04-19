'use strict';

const { AudioContext } = require('..');

const read = require('./utils/read');


(async () => { try {
	
	const context = new AudioContext();
	
	// const clip = await read(`${__dirname}/samples/hit.wav`);
	
	// const musicClip = await new Promise(res => context.decodeAudioData(clip, b => res(b)));
	
	// const gain = context.createGain();
	// gain.gain.value = 0.0625;
	// gain.connect(context.destination);
	
	
	// let isActive;
	// let i = 1;
	
	// Let it settle down
	await new Promise(res => setTimeout(res, 1000));
	
	// console.log('_destruction.js', '1');
	setInterval(async () => {
		
		try {
			const clip = await read(`${__dirname}/samples/hit.wav`);
			// const musicClip = await new Promise(res => context.decodeAudioData(clip, b => res(b)));
		} catch (e) { console.error(e); }
		// if (isActive) {
		// 	// console.log('STILL ACTIVE!');
		// }
		// isActive = true;
		console.log('_destruction.js', '2');
		const musicClipNode = context.createBufferSource();
		musicClipNode.on("desu", () => console.log('_destruction.js', 'DESU'))
		// console.log('_destruction.js', '3');
		// musicClipNode.buffer = musicClip;
		// musicClipNode.connect(gain);
		// // console.log('_destruction.js', '4');
		// musicClipNode.on('ended', () => isActive = false);
		// musicClipNode.on('ended', () => console.log('Ended:', i++));
		// // console.log('_destruction.js', '5');
		// musicClipNode.start(0);
		
	}, 200).unref();
	// console.log('_destruction.js', '6');
	
	// 60 sec
	await new Promise(res => setTimeout(res, 600000));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();

