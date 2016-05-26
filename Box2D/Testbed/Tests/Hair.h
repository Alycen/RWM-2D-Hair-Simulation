#ifndef HAIR_H
#define HAIR_H

class Hair : public Test 
{
public:
	Hair() 
	{
		/*b2Body* ground;

		// Create ground body
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.Set(b2Vec2(-25.0f, 40.0f), b2Vec2(25.0f, 40.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		
		b2PolygonShape shape;
		shape.SetAsBox(0.5f, 0.125f);

		b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = 20.0f;
		fd.friction = 0.2f;
		fd.filter.categoryBits = 0x0001;
		fd.filter.maskBits = 0xFFFF & ~0x0002;

		b2RevoluteJointDef jd;
		jd.collideConnected = false;

		int32 numOfHairs = 10;
		int32 numOfSegments = 10;
		float32 legnth = 15.0f;

		for (int i = 0; i < numOfHairs; i++)
		{
			b2Body* prevBody = ground;
			for (int j = 0; j < numOfSegments; j++)
			{
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(0.5f + 1.0f * i, legnth * j);

				b2Body* body = m_world->CreateBody(&bd);
			}
		}
	}*/

		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.Set(b2Vec2(-30.0f, 35.0f), b2Vec2(20.0f, 35.0f));
			ground->CreateFixture(&shape, 0.0f);
		}

		{
			b2PolygonShape shape;
			shape.SetAsBox(0.5f, 0.125f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 5000.0f;
			fd.friction = 0.2f;
			fd.filter.categoryBits = 0x0001;
			fd.filter.maskBits = 0xFFFF & ~0x0002;

			b2RevoluteJointDef jd;
			jd.collideConnected = false;

			const int32 numOfSegments = 18;
			const float32 x = 35.0f;
			m_ropeDef.localAnchorA.Set(x, 0.0f);

			b2Body* prevBody = ground;
			for (int32 i = 0; i < numOfSegments; ++i)
			{
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(x, 0.5f + 1.0f * i);

				b2Body* body = m_world->CreateBody(&bd);

				body->CreateFixture(&fd);

				b2Vec2 anchor(x, float32(i));
				jd.Initialize(prevBody, body, anchor);
				m_world->CreateJoint(&jd);

				prevBody = body;
			}

			m_ropeDef.localAnchorB.Set(0.0f, 0.0f);

			float32 extraLength = 0.01f;
			m_ropeDef.maxLength = numOfSegments - 1.0f + extraLength;
			m_ropeDef.bodyB = prevBody;
		}

		{
			m_ropeDef.bodyA = ground;
			m_rope = m_world->CreateJoint(&m_ropeDef);
		}
	}

	void Keyboard(int key)
	{
		switch (key)
		{
		case GLFW_KEY_J:
			if (m_rope)
			{
				m_world->DestroyJoint(m_rope);
				m_rope = NULL;
			}
			else
			{
				m_rope = m_world->CreateJoint(&m_ropeDef);
			}
			break;
		}
	}

	void Step(Settings* settings)
	{
		Test::Step(settings);
		g_debugDraw.DrawString(5, m_textLine, "Press (j) to toggle the rope joint.");
		m_textLine += DRAW_STRING_NEW_LINE;
		if (m_rope)
		{
			g_debugDraw.DrawString(5, m_textLine, "Rope ON");
		}
		else
		{
			g_debugDraw.DrawString(5, m_textLine, "Rope OFF");
		}
		m_textLine += DRAW_STRING_NEW_LINE;
	}

	static Test* Create()
	{
		return new Hair;
	}

	b2RopeJointDef m_ropeDef;
	b2Joint* m_rope;
};

#endif