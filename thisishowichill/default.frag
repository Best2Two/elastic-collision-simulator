#version 330 core
			out vec4 FragColor;
			uniform vec2 u_Center;
			uniform vec4 u_Color;
			void main()
			{
				float dist = distance(gl_FragCoord.xy, u_Center);
				if (dist > 50.0) // circle at radius = 50 pixels
					discard;
			FragColor = u_Color;
			};