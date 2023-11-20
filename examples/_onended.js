'use strict';

const { AudioContext } = require('..');

const { readAsBuffer } = require('./utils/read-as-buffer');


(async () => { try {
	
	const context = new AudioContext();
	
	const clip = await readAsBuffer(`${__dirname}/samples/hit.wav`);
	
	const musicClip = await new Promise((res) => context.decodeAudioData(clip, (b) => res(b)));
	
	const gain = context.createGain();
	gain.gain.value = 0.0625;
	
	const musicClipNode = context.createBufferSource();
	
	
	musicClipNode.buffer = musicClip;
	musicClipNode.connect(gain);
	
	gain.connect(context.destination);
	
	
	let isActive;
	let i = 1;
	
	musicClipNode.on('ended', () => isActive = false);
	musicClipNode.on('ended', () => console.log('Played:', i++));
	
	// Let it settle down
	await new Promise((res) => setTimeout(res, 1000));
	
	setInterval(() => {
		if (isActive) {
			console.log('STILL ACTIVE!');
		}
		isActive = true;
		musicClipNode.start(0);
	}, 100).unref();
	
	
	// 60 sec
	await new Promise((res) => setTimeout(res, 60000));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();
