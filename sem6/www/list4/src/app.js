const express = require('express');
const mongoose = require('mongoose');
const userRoutes = require('./routes/users');
const authRoutes = require('./routes/auth');
const bookRoutes = require('./routes/books');
const reviewRoutes = require('./routes/reviews');
require('dotenv').config();

const createApp = async () => {
  const app = express();
  app.use(express.json());

  await mongoose.connect(process.env.MONGODB_URI);

  app.use('/api/users', userRoutes);
  app.use('/api/auth', authRoutes);
  app.use('/api/books', bookRoutes);
  app.use('/api/reviews', reviewRoutes);

  app.use((req, res) => {
    res.status(404).json({ error: 'Endpoint nieznaleziony' });
  });

  return app;
};

module.exports = createApp;
