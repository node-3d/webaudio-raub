'use strict';

const { AudioContext } = require('..');
const { readAsBuffer } = require('./utils/read-as-buffer');


let total = 0;
let num = 0;

const count = 6;
const objects = [];
const scene = [];

const speed = 0.002;
const height = 3;
const offset = 0.5;

const context = new AudioContext();

(async () => { try {
	const clip = await readAsBuffer(`${__dirname}/samples/hit.wav`);
	
	const buffer = await new Promise((res) => context.decodeAudioData(clip, (b) => res(b)));
	
	// Create objects when audio buffer is loaded
	for (let i = 0; i < count; i++) {
		const ball = { y: 0 };
		const audio = {};
		audio.panner = context.createPanner();
		audio.panner.onended = () => {
			console.log('-PAN');
		};
		audio.panner.connect(context.destination);
		audio.isPlaying = false;
		audio.startTime = 0;
		audio.playbackRate = 1;
		audio.play = () => {
			if (audio.isPlaying === true) {
				console.warn( 'Audio is already playing.' );
				return;
			}
			audio.isPlaying = true;
			
			total++;
			console.log(total, Date.now(), '+ABSN:', ++num);
			
			const source = context.createBufferSource();
			source.onended = () => {
				audio.isPlaying = false;
				console.log(total, Date.now(), '-ABSN:', --num);
			};
			
			audio.source = source;
			audio.source.connect(audio.panner);
			
			source.buffer = buffer;
			source.playbackRate.setValueAtTime(audio.playbackRate, audio.startTime);
			audio.startTime = context.currentTime;
			console.log(context.currentTime);
			source.start(audio.startTime, 0);
		};
		
		ball.audio = audio;
		scene.push(ball);
		objects.push(ball);
	}
	
	const render = () => {
		const time = Date.now();
		
		for (let i = 0; i < objects.length; i++) {
			const ball = objects[i];
			const previousHeight = ball.y;
			const al = i * offset + ( time * speed );
			
			ball.y = Math.abs(Math.sin(0.5 * al) * height);
			
			if (ball.y === previousHeight) {
				continue;
			}
			
			if (ball.y < previousHeight) {
				ball.down = true;
			} else {
				// If ball changed direction from down to up
				if (ball.down) {
					ball.audio.play();
					ball.down = false;
				}
			}
		}
	};
	
	setInterval(() => render(), 16);
} catch (e) { console.error(e); } })();
