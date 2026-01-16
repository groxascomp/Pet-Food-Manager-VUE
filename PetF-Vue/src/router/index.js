import { createRouter, createWebHistory } from 'vue-router'

// Components
import Hero from '../components/Hero.vue'
import Company from '../components/Company.vue'

// Pages
import About from '../views/About.vue'
import Services from '../views/Services.vue'
import Blog from '../views/Blog.vue'
import Contact from '../views/Contact.vue'
import Login from '../views/Login.vue'
import LoginAnim from '../views/LoginAnim.vue'
import Level from '../views/Level.vue'

const routes = [
  { path: '/login', component: Login },
  { path: '/login-anim', component: LoginAnim },
  {
    path: '/',
    component: Hero, // Home page
  },
  { path: '/company', component: Company },   // ✅ new route for Company.vue
  { path: '/about', component: About },
  { path: '/services', component: Services },
  { path: '/blog', component: Blog },
  { path: '/contact', component: Contact },
  { path: '/level', component: Level },
  // fallback
  { path: '/:pathMatch(.*)*', redirect: '/' }
]

const router = createRouter({
  history: createWebHistory(),
  routes
})

export default router
