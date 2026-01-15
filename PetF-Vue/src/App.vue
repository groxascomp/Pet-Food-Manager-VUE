<template>
  <div id="app">
    
    
    <NavBar v-if="!isLoginRoute" />

    
    <RouterView />

    <Footer v-if="!isLoginRoute" />
  </div>
</template>

<script setup>
import { computed } from 'vue'
import { useRoute } from 'vue-router'



import NavBar from './components/NavBar.vue'
import Footer from './components/Footer.vue'

const route = useRoute()

// Hide TopBar/NavBar/Footer on login and login-anim routes
const isLoginRoute = computed(() =>
  route.path === '/login' || route.path === '/login-anim'
)
</script>

<style>
@import './App.css';
</style>
