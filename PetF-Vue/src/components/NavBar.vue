<template>
  <nav class="w-full bg-gray-800">
    <div class="px-4 sm:px-6 lg:px-8">
      <div class="flex h-16 items-center justify-between">
        
       
        <RouterLink
          to="/company"
          class="text-white font-bold text-lg hover:text-gray-300 transition"
        >
          PetF.
        </RouterLink>

        
        <div class="hidden sm:flex space-x-4">
          <RouterLink
            to="/"
            class="px-3 py-2 rounded-md text-sm font-medium"
            :class="linkClass('/')"
          >
            Home
          </RouterLink>
          <RouterLink
            to="/about"
            class="px-3 py-2 rounded-md text-sm font-medium"
            :class="linkClass('/about')"
          >
            Feed me!
          </RouterLink>
          <RouterLink
            to="/services"
            class="px-3 py-2 rounded-md text-sm font-medium"
            :class="linkClass('/services')"
          >
            Tracker
          </RouterLink>
          <RouterLink
            to="/blog"
            class="px-3 py-2 rounded-md text-sm font-medium"
            :class="linkClass('/blog')"
          >
            Trivia
          </RouterLink>
          <RouterLink
            to="/level"
            class="flex items-center gap-2 px-3 py-2 rounded-md text-sm font-medium"
            :class="linkClass('/level')"
          >
            <span>Level</span>
            <span
              class="w-3 h-3 rounded-full"
              :class="irStatus === 'detected' ? 'bg-green-500' : 'bg-red-500'"
            ></span>
          </RouterLink>

          <!-- Log-Out -->
          <button
            @click="handleLogout"
            class="hidden sm:inline-block px-3 py-1 text-sm font-medium text-red-500 border border-red-500 rounded hover:bg-red-600 hover:text-white transition"
          >
            Log-Out
          </button>
        </div>

        <!-- Mobile hamburger -->
        <div class="flex items-center sm:hidden">
          <button
            type="button"
            @click="mobileOpen = !mobileOpen"
            class="p-2 rounded-md text-gray-400 hover:bg-gray-700 hover:text-white"
          >
            <span class="sr-only">Open main menu</span>
            <svg
              v-if="mobileOpen"
              class="h-6 w-6"
              fill="none"
              stroke="currentColor"
              stroke-width="1.5"
              viewBox="0 0 24 24"
            >
              <path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" />
            </svg>
            <svg
              v-else
              class="h-6 w-6"
              fill="none"
              stroke="currentColor"
              stroke-width="1.5"
              viewBox="0 0 24 24"
            >
              <path stroke-linecap="round" stroke-linejoin="round" d="M3.75 6.75h16.5M3.75 12h16.5m-16.5 5.25h16.5" />
            </svg>
          </button>
        </div>
      </div>
    </div>

    
    <div v-if="mobileOpen" class="sm:hidden px-2 pt-2 pb-3 space-y-1">
      <RouterLink to="/" class="block px-3 py-2 rounded-md text-base font-medium text-gray-300 hover:bg-gray-700 hover:text-white">
        Home
      </RouterLink>
      <RouterLink to="/about" class="block px-3 py-2 rounded-md text-base font-medium text-gray-300 hover:bg-gray-700 hover:text-white">
        Feed me!
      </RouterLink>
      <RouterLink to="/services" class="block px-3 py-2 rounded-md text-base font-medium text-gray-300 hover:bg-gray-700 hover:text-white">
        Tracker
      </RouterLink>
      <RouterLink to="/blog" class="block px-3 py-2 rounded-md text-base font-medium text-gray-300 hover:bg-gray-700 hover:text-white">
        Trivia
      </RouterLink>
      <RouterLink to="/level" class="flex items-center gap-2 block px-3 py-2 rounded-md text-base font-medium text-gray-300 hover:bg-gray-700 hover:text-white">
        <span>Level</span>
        <span
          class="w-3 h-3 rounded-full"
          :class="irStatus === 'detected' ? 'bg-green-500' : 'bg-red-500'"
        ></span>
      </RouterLink>
      <button
        @click="handleLogout"
        class="block w-full text-left px-3 py-2 text-base font-medium text-red-500 border border-red-500 rounded hover:bg-red-600 hover:text-white transition"
      >
        Log-Out
      </button>
    </div>
  </nav>
</template>

<script setup>
import { ref, onMounted, onUnmounted } from 'vue'
import { useRouter, useRoute, RouterLink } from 'vue-router'

const irStatus = ref('none')
const mobileOpen = ref(false)
const ESP_IP = 'http://10.58.198.63'
const router = useRouter()
const route = useRoute()
const prevStatus = ref('none')

const handleLogout = () => {
  router.push('/login')
}

const fetchStatus = async () => {
  try {
    const res = await fetch(`${ESP_IP}/irStatus`)
    if (!res.ok) throw new Error('Bad response')
    const data = await res.json()

    if (data.status !== 'detected' && prevStatus.value === 'detected') {
      const audio = new Audio('/discord-notification.mp3')
      audio.play().catch(err => console.error('Audio play failed:', err))
    }
    prevStatus.value = data.status
    irStatus.value = data.status
  } catch {
    irStatus.value = 'none'
  }
}

onMounted(() => {
  fetchStatus()
  const interval = setInterval(fetchStatus, 3000)
  onUnmounted(() => clearInterval(interval))
})


const linkClass = (path) => {
  return route.path === path
    ? 'bg-gray-900 text-white'
    : 'text-gray-300 hover:bg-gray-700 hover:text-white'
}
</script>

<style scoped>

</style>
