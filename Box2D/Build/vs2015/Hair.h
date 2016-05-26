#ifndef HAIR_H
#define HAIR_H

class Hair : public Test 
{
public:

	{
		b2Body* ground;

		// Create ground body
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}

		float32 a = 0.5f;
		b2Vec2 h(0.0f, a);

		//b2Body* hairStrand = 
		b2RevoluteJointDef jointDef;
		jointDef.bodyA = ground;
		jointDef.bodyb = hairStrand;

	}

	b2Body* AddHair(b2Body* parent, const b2Vec2& localAnchor, int32 depth, float32 offset, float32 a)
	{

	}

	static Test* Create()
	{
		return new Hair;
	}
};

#endif