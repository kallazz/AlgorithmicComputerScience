const mongoose = require('mongoose');
const bcrypt = require('bcryptjs');

const validatePassword = function(password) {
    if (password.length < 8) {
    return false;
  }
  
    if (!/[A-Z]/.test(password)) {
    return false;
  }
  
    if (!/[!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?]/.test(password)) {
    return false;
  }
  
  return true;
};

const userSchema = new mongoose.Schema({
  username: { 
    type: String, 
    required: [true, 'Nazwa użytkownika jest wymagana'], 
    unique: true,
    trim: true,
    minlength: [3, 'Nazwa użytkownika musi mieć co najmniej 3 znaki']
  },
  email: { 
    type: String, 
    required: [true, 'Email jest wymagany'], 
    unique: true,
    trim: true,
    lowercase: true,
    match: [/^\w+([.-]?\w+)*@\w+([.-]?\w+)*(\.\w{2,3})+$/, 'Nieprawidłowy format email']
  },
  password: { 
    type: String, 
    required: [true, 'Hasło jest wymagane'],
    validate: {
      validator: validatePassword,
      message: 'Hasło musi mieć co najmniej 8 znaków, jedną dużą literę i jeden znak specjalny'
    }
  },
  role: { 
    type: String, 
    enum: {
      values: ['user', 'admin'],
      message: 'Rola musi być user lub admin'
    }, 
    default: 'user' 
  }
}, { timestamps: true });

userSchema.pre('save', async function(next) {
  try {
    this.password = await bcrypt.hash(this.password, 10);
    next();
  } catch (error) {
    next(error);
  }
});

userSchema.methods.comparePassword = async function(candidatePassword) {
  return bcrypt.compare(candidatePassword, this.password);
};

module.exports = {
  User: mongoose.model('User', userSchema)
};