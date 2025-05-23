const request = require('supertest');
const { User } = require('../src/models/User');

describe('Users Routes', () => {
  describe('POST /api/users - Registration', () => {
    it('should register new user with valid data', async () => {
      const userData = {
        username: 'newuser',
        email: 'newuser@example.com',
        password: 'NewUser123!'
      };

      const response = await request(app)
        .post('/api/users')
        .send(userData);

      expect(response.status).toBe(201);
      expect(response.body.username).toBe(userData.username);
      expect(response.body.email).toBe(userData.email);
      expect(response.body.role).toBe('user');
      expect(response.body).not.toHaveProperty('password');
    });

    it('should reject duplicate username', async () => {
      await createTestUser({ username: 'testuser' });

      const response = await request(app)
        .post('/api/users')
        .send({
          username: 'testuser',
          email: 'different@example.com',
          password: 'Test123!'
        });

      expect(response.status).toBe(409);
      expect(response.body.error).toBe('Nazwa użytkownika już istnieje');
    });

    it('should reject duplicate email', async () => {
      await createTestUser({ email: 'test@example.com' });

      const response = await request(app)
        .post('/api/users')
        .send({
          username: 'differentuser',
          email: 'test@example.com',
          password: 'Test123!'
        });

      expect(response.status).toBe(409);
      expect(response.body.error).toBe('Email już istnieje');
    });

    it('should reject invalid email format', async () => {
      const response = await request(app)
        .post('/api/users')
        .send({
          username: 'testuser',
          email: 'invalid-email',
          password: 'Test123!'
        });

      expect(response.status).toBe(400);
      expect(response.body.error).toBe('Nieprawidłowy format email');
    });

    it('should reject short username', async () => {
      const response = await request(app)
        .post('/api/users')
        .send({
          username: 'ab',
          email: 'test@example.com',
          password: 'Test123!'
        });

      expect(response.status).toBe(400);
      expect(response.body.error).toBe('Nazwa użytkownika musi mieć co najmniej 3 znaki');
    });

    it('should reject weak password', async () => {
      const response = await request(app)
        .post('/api/users')
        .send({
          username: 'testuser',
          email: 'test@example.com',
          password: 'weak'
        });

      expect(response.status).toBe(400);
      expect(response.body.error).toBe('Hasło musi mieć co najmniej 8 znaków, jedną dużą literę i jeden znak specjalny');
    });

    it('should reject missing required fields', async () => {
      const response = await request(app)
        .post('/api/users')
        .send({
          username: 'testuser'
          // brak email i password
        });

      expect(response.status).toBe(400);
    });
  });

  describe('GET /api/users - List Users (Admin only)', () => {
    it('should return users list for admin', async () => {
      const admin = await createTestAdmin();
      const user = await createTestUser();
      const token = generateAuthToken(admin._id);

      const response = await request(app)
        .get('/api/users')
        .set('Authorization', `Bearer ${token}`);

      expect(response.status).toBe(200);
      expect(Array.isArray(response.body)).toBe(true);
      expect(response.body.length).toBe(2);
      expect(response.body[0]).not.toHaveProperty('password');
    });

    it('should reject non-admin access', async () => {
      const user = await createTestUser();
      const token = generateAuthToken(user._id);

      const response = await request(app)
        .get('/api/users')
        .set('Authorization', `Bearer ${token}`);

      expect(response.status).toBe(403);
      expect(response.body.error).toBe('Brak uprawnień administratora');
    });

    it('should reject unauthenticated access', async () => {
      const response = await request(app)
        .get('/api/users');

      expect(response.status).toBe(401);
    });
  });

  describe('GET /api/users/:id - Get User Profile', () => {
    it('should return user profile for own profile', async () => {
      const user = await createTestUser();
      const token = generateAuthToken(user._id);

      const response = await request(app)
        .get(`/api/users/${user._id}`)
        .set('Authorization', `Bearer ${token}`);

      expect(response.status).toBe(200);
      expect(response.body._id).toBe(user._id.toString());
      expect(response.body).not.toHaveProperty('password');
    });

    it('should allow admin to view any user profile', async () => {
      const admin = await createTestAdmin();
      const user = await createTestUser();
      const token = generateAuthToken(admin._id);

      const response = await request(app)
        .get(`/api/users/${user._id}`)
        .set('Authorization', `Bearer ${token}`);

      expect(response.status).toBe(200);
      expect(response.body._id).toBe(user._id.toString());
    });

    it('should reject access to other user profile', async () => {
      const user1 = await createTestUser({ username: 'user1', email: 'user1@example.com' });
      const user2 = await createTestUser({ username: 'user2', email: 'user2@example.com' });
      const token = generateAuthToken(user1._id);

      const response = await request(app)
        .get(`/api/users/${user2._id}`)
        .set('Authorization', `Bearer ${token}`);

      expect(response.status).toBe(403);
      expect(response.body.error).toBe('Brak uprawnień');
    });

    it('should return 404 for non-existent user', async () => {
      const admin = await createTestAdmin();
      const token = generateAuthToken(admin._id);
      const nonExistentId = '507f1f77bcf86cd799439011';

      const response = await request(app)
        .get(`/api/users/${nonExistentId}`)
        .set('Authorization', `Bearer ${token}`);

      expect(response.status).toBe(404);
      expect(response.body.error).toBe('Użytkownik nieznaleziony');
    });
  });

  describe('PUT /api/users/:id - Update User', () => {
    it('should update own profile', async () => {
      const user = await createTestUser();
      const token = generateAuthToken(user._id);

      const updateData = {
        username: 'updateduser',
        email: 'updated@example.com'
      };

      const response = await request(app)
        .put(`/api/users/${user._id}`)
        .set('Authorization', `Bearer ${token}`)
        .send(updateData);

      expect(response.status).toBe(200);
      expect(response.body.username).toBe(updateData.username);
      expect(response.body.email).toBe(updateData.email);
    });

    it('should allow admin to update any user', async () => {
      const admin = await createTestAdmin();
      const user = await createTestUser();
      const token = generateAuthToken(admin._id);

      const updateData = {
        username: 'adminupdated',
        email: 'adminupdated@example.com'
      };

      const response = await request(app)
        .put(`/api/users/${user._id}`)
        .set('Authorization', `Bearer ${token}`)
        .send(updateData);

      expect(response.status).toBe(200);
      expect(response.body.username).toBe(updateData.username);
    });

    it('should reject updating other user profile', async () => {
      const user1 = await createTestUser({ username: 'user1', email: 'user1@example.com' });
      const user2 = await createTestUser({ username: 'user2', email: 'user2@example.com' });
      const token = generateAuthToken(user1._id);

      const response = await request(app)
        .put(`/api/users/${user2._id}`)
        .set('Authorization', `Bearer ${token}`)
        .send({ username: 'hacker' });

      expect(response.status).toBe(403);
      expect(response.body.error).toBe('Brak uprawnień');
    });
  });

  describe('DELETE /api/users/:id - Delete User (Admin only)', () => {
    it('should allow admin to delete user', async () => {
      const admin = await createTestAdmin();
      const user = await createTestUser();
      const token = generateAuthToken(admin._id);

      const response = await request(app)
        .delete(`/api/users/${user._id}`)
        .set('Authorization', `Bearer ${token}`);

      expect(response.status).toBe(204);

      // Sprawdź czy użytkownik został usunięty
      const deletedUser = await User.findById(user._id);
      expect(deletedUser).toBeNull();
    });

    it('should reject non-admin deletion', async () => {
      const user = await createTestUser();
      const token = generateAuthToken(user._id);

      const response = await request(app)
        .delete(`/api/users/${user._id}`)
        .set('Authorization', `Bearer ${token}`);

      expect(response.status).toBe(403);
      expect(response.body.error).toBe('Brak uprawnień administratora');
    });

    it('should return 404 for non-existent user', async () => {
      const admin = await createTestAdmin();
      const token = generateAuthToken(admin._id);
      const nonExistentId = '507f1f77bcf86cd799439011';

      const response = await request(app)
        .delete(`/api/users/${nonExistentId}`)
        .set('Authorization', `Bearer ${token}`);

      expect(response.status).toBe(404);
      expect(response.body.error).toBe('Użytkownik nieznaleziony');
    });
  });
});
