const request = require('supertest');
const { User } = require('../src/models/User');

describe('Auth Routes', () => {
  describe('POST /api/auth/login', () => {
    beforeEach(async () => {
      // Stwórz użytkownika testowego
      await new User({
        username: 'testuser',
        email: 'test@example.com',
        password: 'Test123!',
        role: 'user'
      }).save();
    });

    it('should login with valid credentials', async () => {
      const response = await request(app)
        .post('/api/auth/login')
        .send({
          email: 'test@example.com',
          password: 'Test123!'
        });

      expect(response.status).toBe(200);
      expect(response.body).toHaveProperty('token');
      expect(response.body).toHaveProperty('user');
      expect(response.body.user).not.toHaveProperty('password');
      expect(response.body.user.email).toBe('test@example.com');
    });

    it('should reject invalid email', async () => {
      const response = await request(app)
        .post('/api/auth/login')
        .send({
          email: 'wrong@example.com',
          password: 'Test123!'
        });

      expect(response.status).toBe(401);
      expect(response.body.error).toBe('Nieprawidłowe dane logowania');
    });

    it('should reject invalid password', async () => {
      const response = await request(app)
        .post('/api/auth/login')
        .send({
          email: 'test@example.com',
          password: 'wrongpassword'
        });

      expect(response.status).toBe(401);
      expect(response.body.error).toBe('Nieprawidłowe dane logowania');
    });

    it('should reject missing credentials', async () => {
      const response = await request(app)
        .post('/api/auth/login')
        .send({
          email: 'test@example.com'
        });

      expect(response.status).toBe(401);
      expect(response.body.error).toBe('Nieprawidłowe dane logowania');
    });

    it('should reject empty request body', async () => {
      const response = await request(app)
        .post('/api/auth/login')
        .send({});

      expect(response.status).toBe(401);
      expect(response.body.error).toBe('Nieprawidłowe dane logowania');
    });
  });

  describe('Token Validation', () => {
    it('should validate JWT token structure', async () => {
      const user = await createTestUser();
      const token = generateAuthToken(user._id);
      
      const response = await request(app)
        .get(`/api/users/${user._id}`)
        .set('Authorization', `Bearer ${token}`);

      expect(response.status).toBe(200);
      expect(response.body._id).toBe(user._id.toString());
    });

    it('should reject malformed token', async () => {
      const user = await createTestUser();
      
      const response = await request(app)
        .get(`/api/users/${user._id}`)
        .set('Authorization', 'Bearer invalid-token');

      expect(response.status).toBe(401);
      expect(response.body.error).toBe('Nieprawidłowy token');
    });

    it('should reject missing token', async () => {
      const user = await createTestUser();
      
      const response = await request(app)
        .get(`/api/users/${user._id}`);

      expect(response.status).toBe(401);
      expect(response.body.error).toBe('Brak tokenu dostępu');
    });
  });
});
