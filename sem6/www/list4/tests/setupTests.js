const { MongoMemoryServer } = require('mongodb-memory-server');
const mongoose = require('mongoose');
const createApp = require('../app'); // import the async function

let mongoServer;

beforeAll(async () => {
  // Uruchom serwer MongoDB w pamięci
  mongoServer = await MongoMemoryServer.create();
  const mongoUri = mongoServer.getUri();
  
  // Ustaw zmienną środowiskową dla testów
  process.env.MONGODB_URI= mongoUri;
  process.env.NODE_ENV = 'test';
  process.env.JWT_SECRET = 'test-jwt-secret-key';

  app = await createApp(); // wait for connected app
});

afterAll(async () => {
  await mongoose.disconnect();    // Disconnect mongoose from MongoDB
  await mongoServer.stop(); 
});

beforeEach(async () => {
  // Wyczyść wszystkie kolekcje przed każdym testem
  const collections = mongoose.connection.collections;
  for (const key in collections) {
    const collection = collections[key];
    await collection.deleteMany({});
  }
});

// Globalne funkcje pomocnicze
global.createTestUser = async (userData = {}) => {
  const bcrypt = require('bcryptjs');
  const { User } = require('../models/User');
  
  const defaultUserData = {
    username: 'testuser',
    email: 'test@example.com',
    password: 'Test123!',
    role: 'user'
  };
  
  const hashedPassword = await bcrypt.hash(defaultUserData.password, 10);
  const user = new User({
    ...defaultUserData,
    ...userData,
    password: hashedPassword
  });
  
  return await user.save();
};

global.createTestAdmin = async () => {
  return await global.createTestUser({
    username: 'admin',
    email: 'admin@example.com',
    role: 'admin'
  });
};

global.generateAuthToken = (userId) => {
  const jwt = require('jsonwebtoken');
  return jwt.sign({ userId }, process.env.JWT_SECRET, { expiresIn: '24h' });
};
